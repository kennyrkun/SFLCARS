#include "Listener.hpp"

#include <iostream>

Listener::Listener()
{
	failBuffer.loadFromFile("./resources/sounds/error.ogg");
	fail.setBuffer(failBuffer);
	updateBuffer.loadFromFile("./resources/sounds/information_available.ogg");
	update.setBuffer(updateBuffer);
}

Listener::~Listener()
{
	socket.disconnect();
}

bool Listener::connectToServer(const sf::IpAddress& address, const int port)
{
	if (socket.connect(address, port, sf::seconds(10)) != sf::Socket::Done)
		return false;

	selector.add(socket);
	return true;
}

bool Listener::sendToServer(sf::Packet packet)
{
	return (socket.send(packet) != sf::Socket::Status::Done);
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
				std::cerr << "failed to receive packed from server" << std::endl;
				fail.play();
			}
			else
			{
				event = { NetworkEvent::Command::None, time_t(0), packet };
				update.play();
				std::cout << "received and processed packet" << std::endl;
			}
		}
	}
}
