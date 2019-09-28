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
			if (selector.isReady(listener))
			{
				std::cout << "listener is ready:" << std::endl;

				Client* newClient = new Client;
				newClient->socket = new sf::TcpSocket;

				if (listener.accept(*newClient->socket) == sf::Socket::Status::Done)
					if (acceptNewClientConnection(newClient))
						selector.add(*newClient->socket);
				else
				{
					delete newClient->socket;
					delete newClient;
				}
			}
			else
				for (auto& client : clients)
					if (selector.isReady(*client->socket))
						handleIncomingNetTraffic(client);
		}
		else
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

void Server::handleIncomingNetTraffic(Client* client)
{
	std::cout << "socket for client" << client->id << " is ready" << std::endl;

	sf::Packet packet;
	net::Command command;

	client->socket->receive(packet);
	packet >> command;

	std::cout << client->ip.toString() << ": " << command << std::endl;

	sf::Socket::Status status = sf::Socket::Status::Error;

	if (command == net::Command::Login)
	{
		std::string step;
		packet >> step;

		if (step == "step1")
		{
			std::cout << "step1, sending client a random number" << std::endl;

			sf::Packet packet;
			packet << net::Command::Login;
			packet << "step2";
			packet << util::getRandomNumber(0, std::numeric_limits<size_t>::max());

			status = send(packet, client);
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

				status = send(net::Command::LoginSuccess, client);

				client->clientAuthenticated = true;
			}
			else
			{
				status = send(net::Command::LoginFailure, client);
			}
		}
	}
	else if (command == net::Command::Shutdown)
	{
		std::cout << "shutting down" << std::endl;
		status = send(net::Command::ShuttingDown, client);

		running = false;
	}
	else if (command == net::Command::ListClients)
	{
		std::cout << "sending a list of clients" << std::endl;

		sf::Packet packet;
		packet << net::Command::ClientList;

		for (const auto& client : clients)
		{
			std::string clientinformation(std::to_string(client->id) + ";" + client->ip.toString() + ";" + client->name + ";");
			packet << clientinformation;
		}

		status = send(packet, client);
	}
	else if (command == net::Command::Ping)
	{
		status = send(net::Command::Pong, client);
	}
	else if (command == net::Command::SendMessage)
	{
		std::string who, what;

		packet >> who;

		// FIXME: we need to loop over the packet and make sure we get everything in what
		packet >> what;

		std::cout << "sending " << who << ": " << what << std::endl;

		sf::Packet messagePacket;
		messagePacket << "messageDeliver";
		messagePacket << std::to_string(client->id) + ";" + client->ip.toString();
		messagePacket << what;

		sf::Packet messageStatusReportPacket;

		if (who == "everyone")
		{
			for (const auto& client : clients)
			{
				if (client->socket->send(messagePacket) != sf::Socket::Status::Done)
					std::cerr << "failed to send return packet to client" << std::endl;
			}

			messageStatusReportPacket << net::Command::MessageSent;
			messageStatusReportPacket << "The message has been sent to everyone.";
		}
		else
		{
			// find specific ip address

			messageStatusReportPacket << net::Command::MessageRecipientInvalid;
			messageStatusReportPacket << ("The who \"" + who + "\" is not recognised.");
		}

		status = send(messageStatusReportPacket, client);
	}
	else if (command == net::Command::ConnectionRequested)
	{
		std::cout << "client is requesting a connection" << std::endl;

		acceptNewClientConnection(client);
	}
	else if (command == net::Command::StartIntercomToClient)
	{
		std::cout << "starting intercom" << std::endl;

		if (intercomStreams.find(client->id) == intercomStreams.end())
		{
			net::NetworkAudioStream* intercomStream = new net::NetworkAudioStream;
			intercomStreams[client->id] = intercomStream;
			intercomStream->play();

			// id of the client the client wants to talk to
			int id;
			packet >> id;

			std::cout << "with client " << id << std::endl;

			sf::Packet outPacket;
			outPacket << net::Command::IntercomReady;
			outPacket << id;

			status = send(outPacket, client);
		}
		else
			status = send(net::Command::IntercomNotReady, client);
	}
	else if (command == net::Command::IntercomDataSend)
	{
		intercomStreams[client->id]->receiveStep(packet);

		status = sf::Socket::Status::Done;
	}
	else if (command == net::Command::EndIntercomToClient)
	{
		intercomStreams[client->id]->receiveStep(packet, true);

		std::cout << "stopping intercom" << std::endl;

		delete intercomStreams[client->id];
		std::cout << "stopped2" << std::endl;
		intercomStreams[client->id] = nullptr;
		std::cout << "stopped3" << std::endl;
		intercomStreams.erase(client->id);
		std::cout << "stopped4" << std::endl;

		status = sf::Socket::Status::Done;
	}
	else
	{
		status = send(net::Command::UnknownCommand, client);
	}

	if (!packet.endOfPacket())
	{
		std::cout << "WARNING: packet was not fully extracted" << std::endl;
	}

	if (status != sf::Socket::Status::Done)
	{
		std::cout << "packet failed, testing connection to client" << std::endl;

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
	std::cout << "evaluating connection eligibility of a client" << std::endl;

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
	clients.push_back(newClient);

	sf::Packet notifyPacket;
	notifyPacket << net::Command::ConnectionAccepted;
	notifyPacket << newClient->id;

	send(notifyPacket, newClient);
	send(notifyPacket, newClient);
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
