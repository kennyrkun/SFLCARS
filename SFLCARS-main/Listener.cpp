#include "Listener.hpp"

#include <iostream>

Listener::Listener()
{
	buffer.loadFromFile("./resources/sounds/beep3.ogg");
	updateBeep.setBuffer(buffer);
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
		abort();

	sf::Packet packet;
	if (socket.receive(packet) == sf::Socket::Done)
		std::cout << "received data" << std::endl;

	std::cout << "waiting for data" << std::endl;
	if (selector.wait())
	{
		abort();

		if (selector.isReady(socket))
		{
			abort();

			std::cout << "socket is ready: " << std::endl;

			sf::Packet packet;
			if (socket.receive(packet) != sf::Socket::Done)
				std::cerr << "failed to receive packed from server" << std::endl;

			event = { NetworkEvent::Command::None, time_t(0), packet };

			updateBeep.play();

			std::cout << "stuff stuff" << std::endl;
		}
	}
	else
		std::cout << "no data available" << std::endl;
	std::cout << "finished with network data" << std::endl;
}
