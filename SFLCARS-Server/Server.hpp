#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>

#include "Client.hpp"

class Server
{
public:
	Server();

	void run();

private:
	sf::Socket::Status send(sf::Packet& packet, Client* client);

	bool acceptNewClientConnection(Client* newClient);

	void informClientsShutdown();
	bool testClientConnection(Client* client);

	unsigned int totalClients = 0;

	bool running = true;

	sf::TcpListener listener;

	sf::SocketSelector selector;

	std::vector<Client*> clients;

	std::string version = "1";
};

#endif // !SERVER_HPP
