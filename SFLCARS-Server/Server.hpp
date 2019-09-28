#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"

#include <Command.hpp>
#include <NetworkAudioStream.hpp>

#include <SFML/Network.hpp>

class Server
{
public:
	Server();

	void run();

	void handleIncomingNetTraffic(Client* client);

private:
	sf::Socket::Status send(sflcars::utility::network::Command command, Client* client);
	sf::Socket::Status send(sf::Packet& packet, Client* client);

	bool acceptNewClientConnection(Client* newClient);

	bool clientAlreadyConnected(Client* client);

	bool testClientConnection(Client* client);

	unsigned int totalClients = 0;

	bool running = true;

	sf::TcpListener listener;

	sf::SocketSelector selector;

	std::vector<Client*> clients;

	std::string version = "1";

	std::map<int, sflcars::utility::network::NetworkAudioStream*> intercomStreams;
};

#endif // !SERVER_HPP
