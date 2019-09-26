#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <Command.hpp>

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <ctime>

namespace net = sflcars::utility::network;

struct NetworkEvent
{
	net::Command command;

	time_t receivedTime = 0;
	sf::Packet packet;
};

class Listener
{
public:
	Listener();
	~Listener();

	bool connectToServer(const sf::IpAddress& address, const unsigned short port);

	sf::TcpSocket socket;

	sf::Socket::Status send(sf::Packet packet);

	void pollNetworkEvent(NetworkEvent& event);

private:
	sf::SocketSelector selector;

	sf::Sound packetSuccess;
	sf::Sound packetFail;
	sf::Sound serverConnectFail;
	sf::SoundBuffer packetSuccessBuffer;
	sf::SoundBuffer packetFailBuffer;
	sf::SoundBuffer serverConnectFailBuffer;
};

#endif // !LISTENER_HPP
