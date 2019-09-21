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
	~Listener();

	bool connectToServer(const sf::IpAddress& address, const int port);

	sf::TcpSocket socket;

	bool sendToServer(sf::Packet packet);

	void pollNetworkEvent(NetworkEvent& event);

private:
	sf::SocketSelector selector;

	sf::Sound update;
	sf::Sound fail;
	sf::SoundBuffer updateBuffer;
	sf::SoundBuffer failBuffer;
};

#endif // !LISTENER_HPP
