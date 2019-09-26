#include "Listener.hpp"

#include <iostream>

Listener::Listener()
{
	packetFailBuffer.loadFromFile("./resources/sounds/error.ogg");
	packetFail.setBuffer(packetFailBuffer);
	packetFail.setVolume(50.0f);

	serverConnectFailBuffer.loadFromFile("./resources/sounds/fail2.ogg");
	serverConnectFail.setBuffer(serverConnectFailBuffer);
	serverConnectFail.setVolume(50.0f);

	packetSuccessBuffer.loadFromFile("./resources/sounds/network/set.ogg");
	packetSuccess.setBuffer(packetSuccessBuffer);
	packetSuccess.setVolume(50.0f);
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
		serverConnectFail.play();
		return false;
	}

	selector.add(socket);
	return true;
}

sf::Socket::Status Listener::send(net::Command command)
{
	sf::Packet packet;
	packet << command;
	return send(packet);
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
				packetFail.play();
			}
			else
			{
				event = { net::Command::None, time_t(0), packet };
				event.packet >> event.command;
				std::cout << "received and processed packet (" << event.command << ")" << std::endl;
				packetSuccess.play();
			}
		}
	}
}
