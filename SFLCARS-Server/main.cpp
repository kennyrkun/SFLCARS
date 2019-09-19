#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

struct Client
{
	std::string name;

	sf::IpAddress ip;
	int id;

	sf::TcpSocket* socket;
};

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

						bool duplicateClient = false;
						for (const auto& client : clients)
							if (client.ip == newClient.ip)
							{
								duplicateClient = true;
								break;
							}

						sf::Packet notifyPacket;

						if (duplicateClient)
						{
							notifyPacket << "connectionRejected";
							notifyPacket << "duplicateClient";
							notifyPacket << "A client with this IP address is already connected.";
						}
						else
						{
							newClient.id = totalClients++;
							selector.add(*newClient.socket);
							clients.push_back(newClient);

							notifyPacket << "connectionAccepted";
						}

						if (newClient.socket->send(notifyPacket) != sf::Socket::Status::Done)
							std::cerr << "failed to send return packet to client" << std::endl;

						if (duplicateClient)
						{
							newClient.socket->disconnect();
							delete newClient.socket;
						}
						else
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
									delete client.socket;
									//clients.erase(std::remove(clients.begin(), clients.end(), client));
								}
								else if (client.socket->getRemoteAddress() == sf::IpAddress::None)
								{
									std::cout << "client disconnected" << std::endl;
									client.socket->disconnect();
									delete client.socket;
									// TODO: delete client
								}
							}
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