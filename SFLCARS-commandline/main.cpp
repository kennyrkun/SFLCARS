#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include <sstream>

int main()
{
	sf::IpAddress remoteAddress = sf::IpAddress::LocalHost;
	int remotePort = 51425;

	std::string address;
	std::cout << "SFLCARS server address: ";
	std::getline(std::cin, address);
	if (address.empty())
		remoteAddress = sf::IpAddress::LocalHost;
	else
		remoteAddress = address;

	std::string port;
	std::cout << "SFLCARS server port: ";
	std::getline(std::cin, port);
	if (port.empty())
		remotePort = 51425;
	else
		remotePort = std::stoi(port);

	int id = -1;

	sf::TcpSocket tcpSocket;

	std::cout << "attempting to connect to SFLCARS server at " << remoteAddress << " on port " << remotePort << std::endl;

	if (tcpSocket.connect(remoteAddress, remotePort, sf::seconds(15)) != sf::Socket::Status::Done)
		std::cerr << "failed to connect to SFLCARS server" << std::endl;
	else
	{
		std::cout << "connection was successful" << std::endl;

		{
			sf::Packet packet;
			tcpSocket.receive(packet);

			std::string command;
			packet >> command;

			std::cout << "server: " << command << std::endl;

			if (command != "connectionAccepted")
			{
				std::cerr << "connection was rejected by the server" << std::endl;
				return -1;
			}
		}

		while (true)
		{
			if (tcpSocket.getRemoteAddress() == sf::IpAddress::None)
			{ 
				std::cerr << "not connected" << std::endl;
				break;
			}

			std::string rawCommand, command;
		
			std::cout << "> ";

			std::getline(std::cin, rawCommand);

			if (rawCommand == "/quit")
			{
				tcpSocket.disconnect();
				break;
			}

			sf::Packet packet;
			std::stringstream iss(rawCommand);
			while (iss >> command)
				packet << command;

			if (tcpSocket.send(packet) != sf::Socket::Status::Done)
				std::cerr << "failed to send command packet to server" << std::endl;
			else
			{
				// TODO: go back a line and then write the server response
				std::cout << "...";

				sf::Packet recievedPacket;
				std::string serverCommand;

				if (tcpSocket.receive(recievedPacket) != sf::Socket::Status::Done)
					std::cerr << "failed to recieve response from server" << std::endl;
				else
				{
					std::string packet;

					recievedPacket >> packet;

					while (!recievedPacket.endOfPacket())
					{
						std::string temp;
						recievedPacket >> temp;
						packet += ("\n" + temp);
					}

					std::cout << "\rserver: " << packet << std::endl;
				}
			}
		}
	}

	std::cout << "press most keys to continue..." << std::endl;
	std::cin.get();

	return 0;
}
