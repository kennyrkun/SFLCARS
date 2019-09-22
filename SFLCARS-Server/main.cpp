#include "Client.hpp"

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

enum class Command
{
	Shutdown,
	Status,
	Information,
	ListClients
};

class Server
{
public:
	Server()
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
		}
	}

	void run()
	{
		std::cout << "starting SFLCARS server" << std::endl;

		if (listener.listen(12345) != sf::Socket::Status::Done)
		{
			std::cerr << "failed to bind listener to port" << std::endl;
			return;
		}
		else
			std::cout << "bound to port" << std::endl;

		listener.setBlocking(false);

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
					std::cout << "something hit the listener" << std::endl;
					Client newClient;
					newClient.socket = new sf::TcpSocket;
					if (listener.accept(*newClient.socket) == sf::Socket::Status::Done)
					{
						// authentication

						newClient.ip = newClient.socket->getRemoteAddress();

						for (const auto& client : clients)
							if (client.ip == newClient.ip)
							{
								sf::Packet notifyPacket;

								notifyPacket << "connectionRejected";
								notifyPacket << "duplicateClient";
								notifyPacket << "A client with this IP address is already connected.";

								if (newClient.socket->send(notifyPacket) != sf::Socket::Status::Done)
									std::cerr << "failed to send return packet to client" << std::endl;

								newClient.socket->disconnect();
								delete newClient.socket;

								std::cout << "denied duplicate client" << std::endl;

								break;
							}


						sf::Packet notifyPacket;

						newClient.id = totalClients++;
						selector.add(*newClient.socket);
						clients.push_back(newClient);

						notifyPacket << "connectionAccepted";

						if (newClient.socket->send(notifyPacket) != sf::Socket::Status::Done)
							std::cerr << "failed to send return packet to client" << std::endl;

						std::cout << "accepted new client" << std::endl;
					}
					else
						delete newClient.socket;
				}
				else
				{
					for (auto& client : clients)
					{
						if (selector.isReady(*client.socket))
						{
							sf::Packet packet, responsePacket;
							std::string command, responseCommand;

							client.socket->receive(packet);
							packet >> command;

							std::cout << client.ip.toString() << ": " << command << std::endl;

							if (command == "login")
							{
								std::string step;
								packet >> step;

								if (step == "step1")
								{
									std::cout << "step1, sending client a random number" << std::endl;

									responseCommand = "login";
									responsePacket << responseCommand;
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

										responseCommand = "loginSuccess";
										responsePacket << responseCommand;

										client.clientAuthenticated = true;
									}
									else
									{
										responseCommand = "loginFailure";
										responsePacket << "The password did not match the locally stored password.";
									}
								}
							}
							else if (command == "shutdown")
							{
								std::cout << "shutting down" << std::endl;
								responseCommand = "shutting the heck down boys";
								responsePacket << responseCommand;

								running = false;
							}
							else if (command == "listClients")
							{
								std::cout << "sending a list of clients" << std::endl;

								responseCommand = "clientList";
								responsePacket << responseCommand;

								for (const auto& client : clients)
								{
									std::string clientinformation(std::to_string(client.id) + ";" + client.ip.toString() + ";");
									responsePacket << clientinformation;
								}
							}
							else if (command == "ping")
							{
								responseCommand = "pong";
								responsePacket << responseCommand;
							}
							else if (command == "getVersion")
							{
								responseCommand = "giveVersion";
								responsePacket << responseCommand;
								responsePacket << version;
							}
							else if (command == "messageSend")
							{
								std::string who, what;

								packet >> who;

								// FIXME: we need to loop over the packet and make sure we get everything in what
								packet >> what;

								std::cout << "sending " << who << ": " << what << std::endl;

								sf::Packet message;
								message << "messageDeliver";
								message << (std::to_string(client.id) + ";" + client.ip.toString());
								message << what;

								if (who == "everyone")
								{
									for (const auto& client : clients)
									{
										if (client.socket->send(message) != sf::Socket::Status::Done)
											std::cerr << "failed to send return packet to client" << std::endl;
									}

									responseCommand = "messageSent";
									responsePacket << "The message has been sent to everyone.";
								}
								else
								{
									// find specific ip address

									responseCommand = "messageInvalid";
									responsePacket << responseCommand;
									responsePacket << ("The who \"" + who + "\" is not recognised.");
								}
							}
							else
							{
								responseCommand = "\"" + command + "\" acknowledged; command unknown";
								responsePacket << responseCommand;
							}

							if (client.socket->send(responsePacket) != sf::Socket::Status::Done)
							{
								std::cerr << "failed to send return packet to client" << std::endl;

								if (client.socket->send(responsePacket) == sf::Socket::Status::Disconnected)
								{
									std::cout << "client disconnected" << std::endl;
									client.socket->disconnect();
									//std::remove(clients.begin(), clients.end(), client);
									delete client.socket;
								}
								else if (client.socket->getRemoteAddress() == sf::IpAddress::None)
								{
									std::cout << "client disconnected" << std::endl;
									client.socket->disconnect();
									delete client.socket;
									// TODO: delete client
								}
							}

							if (client.socket->send(responsePacket) != sf::Socket::Status::Done)
								std::cerr << "failed to send return packet to client" << std::endl;
						}
					}
				}
			}

			sf::sleep(sf::milliseconds(100));
		}

		std::cout << "exiting SFLCARS server." << std::endl;

		// let all the clients know we're shutting down
		for (auto& client : clients)
		{
			std::string responseCommand = "disconnect";

			sf::Packet responsePacket;
			responsePacket << responseCommand;
			responsePacket << "shuttingDown";
			if (client.socket->send(responsePacket) != sf::Socket::Status::Done)
				std::cerr << "failed to send return packet to client" << std::endl;

			client.socket->disconnect();
			delete client.socket;
		}

		std::cin.get();
	}

private:
	unsigned int totalClients = 0;

	bool running = true;

	sf::TcpListener listener;

	sf::SocketSelector selector;

	std::vector<Client> clients;

	std::string version = "1";
};

int main()
{
	Server server;

	server.run();

	std::cin.get();

	return 0;
}