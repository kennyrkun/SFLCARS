#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <SFML/Network.hpp>

#include <vector>

struct NetworkEvent
{
	time_t receivedTime;
	sf::Packet packet;
};

class Listener
{
public:
	Listener();

	sf::TcpSocket socket;

	void Update();

	std::vector<NetworkEvent> eventQueue;
private:
	sf::SocketSelector selector;
};

#endif // !LISTENER_HPP
