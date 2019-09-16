#include <SFML/Network.hpp>

#include <iostream>
#include <string>

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

	sf::TcpSocket tcpSocket;

	std::cout << "attempting to connect to SFLCARS server at " << remoteAddress << " on port " << remotePort << std::endl;

	if (tcpSocket.connect(remoteAddress, remotePort, sf::seconds(15)) != sf::Socket::Status::Done)
		std::cerr << "failed to connect to SFLCARS server" << std::endl;
	else
	{
		std::cout << "connected successfully" << std::endl;

		while (true)
		{
			if (tcpSocket.getRemoteAddress() == sf::IpAddress::None)
			{ 
				std::cerr << "not connected" << std::endl;
				return 0;
			}

			std::string command;
		
			std::cout << "> ";

			std::getline(std::cin, command);

			if (command == "/quit")
			{
				tcpSocket.disconnect();
				break;
			}

			sf::Packet packet;
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
					recievedPacket >> serverCommand;
					std::cout << "\rserver: " << serverCommand << std::endl;
				}
			}
		}
	}

	std::cout << "press most keys to continue..." << std::endl;
	std::cin.get();

	return 0;
}
