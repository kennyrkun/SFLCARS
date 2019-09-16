#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

struct Client
{
	sf::IpAddress ip;
	int id;

	sf::TcpSocket* socket;
};

class Server
{
public:
	void run()
	{
		std::cout << "starting SFLCARS server" << std::endl;

		if (listener.listen(51425) != sf::Socket::Status::Done)
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
			if (selector.wait(sf::seconds(1.0f)))
			{
				std::cout << "something is ready:" << std::endl;

				if (selector.isReady(listener))
				{
					std::cout << "something hit the listener" << std::endl;
					Client newClient;
					newClient.socket = new sf::TcpSocket;
					if (listener.accept(*newClient.socket) == sf::Socket::Status::Done)
					{
						newClient.id = totalClients++;
						newClient.ip = newClient.socket->getRemoteAddress();
						selector.add(*newClient.socket);
						clients.push_back(newClient);
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

							std::cout << "client" + client.id << ": " << command << std::endl;

							if (command == "shutdown")
							{
								std::cout << "shutting down" << std::endl;
								responseCommand = "\"" + command + "\" acknowledged, shutting down";

								// let the client know we got their command
								responsePacket << responseCommand;
								if (client.socket->send(responsePacket) != sf::Socket::Status::Done)
									std::cerr << "failed to send return packet to client" << std::endl;

								running = false;
							}
							else
							{
								responseCommand = "\"" + command + "\" acknowledged; command unknown";

								responsePacket << responseCommand;
								if (client.socket->send(responsePacket) != sf::Socket::Status::Done)
									std::cerr << "failed to send return packet to client" << std::endl;
							}
						}
					}
				}
			}

			sf::sleep(sf::seconds(1));
		}

		std::cout << "exiting SFLCARS server." << std::endl;

		// let all the clients know we're shutting down
		for (auto& client : clients)
		{
			std::string responseCommand = "shutting down";

			sf::Packet responsePacket;
			responsePacket << responseCommand;
			if (client.socket->send(responsePacket) != sf::Socket::Status::Done)
				std::cerr << "failed to send return packet to client" << std::endl;

			client.socket->disconnect();

			delete client.socket;
		}

		std::cin.get();
	}

	unsigned int totalClients = 0;

	bool running = true;

	sf::TcpListener listener;

	sf::SocketSelector selector;

	std::vector<Client> clients;
};

int main()
{
	Server server;

	server.run();

	return 0;
}
