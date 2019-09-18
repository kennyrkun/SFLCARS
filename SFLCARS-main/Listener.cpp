#include "Listener.hpp"

#include <iostream>

Listener::Listener()
{
	selector.add(socket);

	buffer.loadFromFile("./resources/sounds/beep_set.ogg");
	updateBeep.setBuffer(buffer);
}

bool Listener::connectToServer(const sf::IpAddress& address, const int port)
{
	if (socket.connect(address, port, sf::seconds(10)) != sf::Socket::Done)
		return false;

	return true;
}

bool Listener::sendToServer(sf::Packet packet)
{
	return (socket.send(packet) != sf::Socket::Status::Done);
}

void Listener::pollNetworkEvent(NetworkEvent& event)
{
	if (selector.wait(sf::seconds(1.0f)))
	{
		std::cout << "selector is ready: " << std::endl;

		if (selector.isReady(socket))
		{
			std::cout << "socket is ready: " << std::endl;

			sf::Packet packet;
			if (socket.receive(packet) != sf::Socket::Done)
				std::cerr << "failed to receive packed from server" << std::endl;

			event = { NetworkEvent::Command::None, time_t(0), packet };

			updateBeep.play();

			std::cout << "stuff stuff" << std::endl;
		}
	}
}
