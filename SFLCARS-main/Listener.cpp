#include "Listener.hpp"
#include "AppEngine.hpp"

#include "InitialiseState.hpp"

#include <iostream>

Listener::Listener(AppEngine* app) : app(app)
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

	serverConnectionLostBuffer.loadFromFile("./resources/sounds/critical_long.ogg");
	serverConnectionLost.setBuffer(serverConnectionLostBuffer);
}

Listener::~Listener()
{
	std::cout << "shutting down listener" << std::endl;

	send(net::ServerCommand::Disconnecting);

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

sf::Socket::Status Listener::send(net::ServerCommand command)
{
	sf::Packet packet;
	packet << command;
	return send(packet);
}

sf::Socket::Status Listener::send(sf::Packet packet)
{
	sf::Socket::Status status = socket.send(packet);

	if (status != sf::Socket::Status::Done)
	{
		std::cerr << "failed to send packet to server (" << status << ")" << std::endl;
		packetFail.play();
	}

	return status;
}

void Listener::pollNetworkEvent(NetworkEvent& event)
{
	// Because we're probably not connected to the server yet
	if (socket.getRemoteAddress() == sf::IpAddress::None)
		return;

	if (selector.wait(sf::milliseconds(10)))
	{
		std::cout << "selector (";

		if (selector.isReady(socket))
		{
			std::cout << "socket)" << std::endl;

			sf::Packet packet;
			sf::Socket::Status status = socket.receive(packet);
			if (status != sf::Socket::Status::Done)
			{
				if (status == sf::Socket::Status::Disconnected)
				{
					std::cerr << "server has disconnected" << std::endl;
					socket.disconnect();

					serverConnectionLost.play();

					app->PopState(app->states.size());
					app->ChangeState(new InitialiseState);
					// TODO: clear all app states and go back to initialisestate
				}

				std::cerr << "failed to receive packet from server" << std::endl;
				packetFail.play();
			}
			else
			{
				event = { net::ClientCommand::None, time_t(0), packet };
				event.packet >> event.command;
				std::cout << "received and processed packet (" << (int)event.command << ")" << std::endl;

				// don't play sounds for reptitive commands
				if (event.command != net::ClientCommand::IntercomDataReceive)
					packetSuccess.play();
			}
		}
		else
		{
			std::cout << "unknown)" << std::endl;
			std::cerr << "This should neverr happen" << std::endl;
			abort();
		}
	}
}
