#include "Server.hpp"

#include <Password.hpp>
#include <SettingsParser.hpp>
#include <Utility.hpp>

#include <SFML/Network.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// TODO: send commands instead of strings

namespace fs = std::filesystem;
namespace util = sflcars::utility;
namespace pass = sflcars::utility::password;
namespace net = sflcars::utility::network;

Server::Server()
{
	const std::string BASE = "./sflcars_server/";
	const std::string ACCOUNTS = BASE + "accounts/";

	if (!fs::exists(BASE))
		fs::create_directory(BASE);

	if (!fs::exists(ACCOUNTS))
		fs::create_directory(ACCOUNTS);

	if (fs::is_empty(ACCOUNTS))
	{
		std::cout << "no user accounts are present" << std::endl;

		std::string username = "admin";
		std::string password = "admin";
		std::string hashedPassword = pass::hashString(password);

		fs::create_directory(ACCOUNTS + username);

		std::ofstream createAccountFile(ACCOUNTS + username + "/account.dat", std::ios::trunc);

		if (!createAccountFile.is_open())
		{
			std::cerr << "failed to create default account file" << std::endl;
			abort();
		}
		else
			createAccountFile.close();

		util::SettingsParser parser(ACCOUNTS + username + "/account.dat");
		parser.set("username", username);
		parser.set("hashed_password", hashedPassword);
		parser.set("elevated_privileges", true);
	}
}

void Server::run()
{
	std::cout << "starting SFLCARS server" << std::endl;

	if (listener.listen(12345) != sf::Socket::Status::Done)
	{
		std::cerr << "failed to bind listener to port" << std::endl;
		abort();
	}
	else
		std::cout << "Listener bound to port " << listener.getLocalPort() << std::endl;

	std::cout << "this server's local ip address is: " << sf::IpAddress::getLocalAddress() << std::endl;
	std::cout << "this server's public ip address is: " << sf::IpAddress::getPublicAddress() << std::endl;

	selector.add(listener);

	while (running)
	{
		// selector.wait returns true if something inside of it is ready
		// returns false if nothing is ready
		if (selector.wait())
		{
			std::cout << "something is ready:" << std::endl;

			if (selector.isReady(listener))
			{
				std::cout << "listener is ready:" << std::endl;

				Client* newClient = new Client;
				newClient->socket = new sf::TcpSocket;

				if (listener.accept(*newClient->socket) == sf::Socket::Status::Done)
					acceptNewClientConnection(newClient);
				else
				{
					delete newClient->socket;
					delete newClient;
				}
			}
			else
			{
				for (auto& client : clients)
				{
					if (selector.isReady(*client->socket))
					{
						std::cout << "client" << client->id << " socket is ready" << std::endl;

						sf::Packet packet, responsePacket;

						net::Command command;

						client->socket->receive(packet);
						packet >> command;

						std::cout << client->ip.toString() << ": " << command << std::endl;

						if (command == net::Command::Login)
						{
							std::string step;
							packet >> step;

							if (step == "step1")
							{
								std::cout << "step1, sending client a random number" << std::endl;

								responsePacket << net::Command::Login;
								responsePacket << "step2";
								responsePacket << util::getRandomNumber(0, std::numeric_limits<size_t>::max());
							}
							else if (step == "step4")
							{
								std::cout << "step4, testing password" << std::endl;

								std::string username, randoHash, superHash;

								packet >> username;
								packet >> randoHash;
								packet >> superHash;

								// step 5
								util::SettingsParser parser("./sflcars_server/accounts/" + username + "/account.dat");

								std::string local_passwordHash;
								parser.get("hashed_password", local_passwordHash);

								std::string local_superHash = pass::hashString(local_passwordHash + randoHash);

								// step 6
								if (local_superHash == superHash)
								{
									std::cout << "success!" << std::endl;

									responsePacket << net::Command::LoginSuccess;

									client->clientAuthenticated = true;
								}
								else
								{
									responsePacket << net::Command::LoginFailure;
									responsePacket << "The password did not match the locally stored password.";
								}
							}
						}
						else if (command == net::Command::Shutdown)
						{
							std::cout << "shutting down" << std::endl;
							responsePacket << net::Command::ShuttingDown;

							running = false;
						}
						else if (command == net::Command::ListClients)
						{
							std::cout << "sending a list of clients" << std::endl;

							responsePacket << net::Command::ClientList;

							for (const auto& client : clients)
							{
								std::string clientinformation(std::to_string(client->id) + ";" + client->ip.toString() + ";" + client->name + ";");
								responsePacket << clientinformation;
							}
						}
						else if (command == net::Command::Ping)
						{
							responsePacket << net::Command::Pong;
						}
						else if (command == net::Command::Version)
						{
							responsePacket << net::SubCommand::MyVersion;
							responsePacket << version;
						}
						else if (command == net::Command::SendMessage)
						{
							std::string who, what;

							packet >> who;

							// FIXME: we need to loop over the packet and make sure we get everything in what
							packet >> what;

							std::cout << "sending " << who << ": " << what << std::endl;

							sf::Packet message;
							message << "messageDeliver";
							message << std::to_string(client->id) + ";" + client->ip.toString();
							message << what;

							if (who == "everyone")
							{
								for (const auto& client : clients)
								{
									if (client->socket->send(message) != sf::Socket::Status::Done)
										std::cerr << "failed to send return packet to client" << std::endl;
								}

								responsePacket << net::Command::MessageSent;
								responsePacket << "The message has been sent to everyone.";
							}
							else
							{
								// find specific ip address

								responsePacket << net::Command::MessageRecipientInvalid;
								responsePacket << ("The who \"" + who + "\" is not recognised.");
							}
						}
						else if (command == net::Command::ConnectionRequested)
						{
							std::cout << "client is requesting a connection" << std::endl;

							if (clientAlreadyConnected(client))
							{
								sf::Packet notifyPacket;

								notifyPacket << net::Command::ConnectionRejected;
								notifyPacket << "duplicateClient";
								notifyPacket << "A client with this IP address is already connected.";

								send(notifyPacket, client);


								// TODO: remove client
								client->socket->disconnect();
								delete client->socket;

								std::cout << "denied connection from duplicate client" << std::endl;
							}
							else
							{
								sf::Packet notifyPacket;
								notifyPacket << net::Command::ConnectionAccepted;
								notifyPacket << client->id;

								send(notifyPacket, client);

								std::cout << "accepted new client" << client->id << std::endl;
							}
						}
						else if (command == net::Command::StartIntercomToClient)
						{
							std::cout << "starting intercom" << std::endl;
							intercomAudio.play();
						}
						else if (command == net::Command::IntercomDataSend)
						{
							std::cout << "processing intercom data" << std::endl;
							intercomAudio.receiveStep(packet);
						}
						else if (command == net::Command::EndIntercomToClient)
						{
							std::cout << "stopping intercom" << std::endl;
							intercomAudio.stop();
						}
						else if (command == net::Command::IntercomDataSend)
						{
							
						}
						else
						{
							responsePacket << net::Command::None;
							responsePacket << "\"" + std::to_string(command) + "\" acknowledged; command unknown";
						}

						if (send(responsePacket, client) != sf::Socket::Status::Done)
						{
							if (!testClientConnection(client))
							{
								std::cerr << "connection to client has been lost, disconnecting them." << std::endl;
								client->socket->disconnect();
								delete client->socket;
								clients.erase(std::remove(clients.begin(), clients.end(), client));
								delete client;
								std::cout << "clients: " << clients.size() << std::endl;

								if (clients.size() < 1)
								{
									std::cout << "all connections have been closed, cleaning up" << std::endl;
									selector.clear();
									selector.add(listener);
									totalClients = 0;
								}
							}
						}
					}
				}
			}
		}

		sf::sleep(sf::milliseconds(100));
	}

	std::cout << "exiting SFLCARS server." << std::endl;

	for (auto& client : clients)
	{
		send(net::Command::ShuttingDown, client);
		client->socket->disconnect();
		delete client->socket;
		// TODO: remove client
	}

	std::cin.get();
}

sf::Socket::Status Server::send(net::Command command, Client* client)
{
	sf::Packet packet;
	packet << command;

	return send(packet, client);
}

sf::Socket::Status Server::send(sf::Packet& packet, Client* client)
{
	sf::Socket::Status status = client->socket->send(packet);

	if (status != sf::Socket::Status::Done)
		std::cerr << "failed to send packet to client (" << status << ")" << std::endl;

	return status;
}

bool Server::acceptNewClientConnection(Client* newClient)
{
	std::cout << "evaluating connection of new client" << std::endl;

	if (clientAlreadyConnected(newClient))
	{
		sf::Packet notifyPacket;

		notifyPacket << net::Command::ConnectionRejected;
		notifyPacket << "duplicateClient";
		notifyPacket << "A client with this IP address is already connected.";

		send(notifyPacket, newClient);

		newClient->socket->disconnect();
		delete newClient->socket;

		std::cout << "denied duplicate connection from client" << std::endl;

		return false;
	}

	newClient->id = totalClients++;
	selector.add(*newClient->socket);
	clients.push_back(newClient);

	sf::Packet notifyPacket;
	notifyPacket << net::Command::ConnectionAccepted;
	notifyPacket << newClient->id;

	send(notifyPacket, newClient);

	std::cout << "accepted new client" << newClient->id << std::endl;

	return true;
}

bool Server::clientAlreadyConnected(Client* client)
{
	for (const auto& clientx : clients)
		if (clientx->ip == client->socket->getRemoteAddress())
			return true;

	return false;
}

bool Server::testClientConnection(Client* client)
{
	std::cout << "Testing connecting to " << client->id << std::endl;
	
	sf::Packet connectionTest;
	connectionTest << "connectionTest";

	if (client->socket->send(connectionTest) == sf::Socket::Status::Disconnected)
		return false;
	else if (client->socket->getRemoteAddress() == sf::IpAddress::None)
		return false;

	return true;
}
