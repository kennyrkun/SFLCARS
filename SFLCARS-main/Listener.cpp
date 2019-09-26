#include "Listener.hpp"

#include <iostream>

Listener::Listener()
{
	failBuffer.loadFromFile("./resources/sounds/error.ogg");
	fail.setBuffer(failBuffer);
	fail.setVolume(50.0f);
	updateBuffer.loadFromFile("./resources/sounds/network/set.ogg");
	packetReceived.setBuffer(updateBuffer);
	packetReceived.setVolume(50.0f);
}

Listener::~Listener()
{
	sf::Packet packet;
	packet << net::Command::Disconnect;

	send(packet);

	socket.disconnect();
}

bool Listener::connectToServer(const sf::IpAddress& address, const unsigned short port)
{
	if (socket.connect(address, port, sf::seconds(3)) != sf::Socket::Done)
	{
		fail.play();
		return false;
	}

	selector.add(socket);
	return true;
}

sf::Socket::Status Listener::send(sf::Packet packet)
{
	sf::Socket::Status status = socket.send(packet);

	if (status != sf::Socket::Status::Done)
		std::cerr << "failed to send packet to server (" << status << ")" << std::endl;

	return status;
}

void Listener::pollNetworkEvent(NetworkEvent& event)
{
	if (socket.getRemoteAddress() == sf::IpAddress::None)
		return;

	if (selector.wait(sf::milliseconds(10)))
	{
		std::cout << "something is ready: " << std::endl;

		if (selector.isReady(socket))
		{
			std::cout << "socket is ready: " << std::endl;

			sf::Packet packet;
			sf::Socket::Status status = socket.receive(packet);
			if (status != sf::Socket::Status::Done)
			{
				if (status == sf::Socket::Status::Disconnected)
				{
					std::cerr << "server has disconnected" << std::endl;
					socket.disconnect();
					abort();
					// TODO: don't break so horribly
				}

				std::cerr << "failed to receive packed from server" << std::endl;
				fail.play();
			}
			else
			{
				event = { net::Command::None, time_t(0), packet };
				event.packet >> event.command;
				std::cout << "received and processed packet (" << event.command << ")" << std::endl;
				packetReceived.play();
			}
		}
	}
}
