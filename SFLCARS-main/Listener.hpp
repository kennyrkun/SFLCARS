#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <ctime>

struct NetworkEvent
{
	enum class Command
	{
		None,

		Ping,
		Disconnect,
		MessageDeliver,
	} command;

	time_t receivedTime = 0;
	sf::Packet packet;
};

class Listener
{
public:
	Listener();

	bool connectToServer(const sf::IpAddress& address, const int port);

	sf::TcpSocket socket;

	bool sendToServer(sf::Packet packet);

	void pollNetworkEvent(NetworkEvent& event);

private:
	sf::SocketSelector selector;

	sf::Sound updateBeep;
	sf::SoundBuffer buffer;
};

#endif // !LISTENER_HPP
