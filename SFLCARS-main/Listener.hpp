#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "NetworkEvent.hpp"

#include <Command.hpp>

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <ctime>

class AppEngine;

class Listener
{
public:
	Listener(AppEngine* app);
	~Listener();

	bool connectToServer(const sf::IpAddress& address, const unsigned short port);

	sf::TcpSocket socket;

	sf::Socket::Status send(net::ServerCommand command);
	sf::Socket::Status send(sf::Packet packet);

	void pollNetworkEvent(NetworkEvent& event);

private:
	AppEngine* app;

	sf::SocketSelector selector;

	sf::Sound packetSuccess;
	sf::Sound packetFail;
	sf::Sound serverConnectFail;
	sf::Sound serverConnectionLost;
	sf::SoundBuffer packetSuccessBuffer;
	sf::SoundBuffer packetFailBuffer;
	sf::SoundBuffer serverConnectFailBuffer;
	sf::SoundBuffer serverConnectionLostBuffer;
};

#endif // !LISTENER_HPP
