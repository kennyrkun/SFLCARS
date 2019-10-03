#include "Command.hpp"

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::ServerCommand& command)
{
	int x = static_cast<int>(command);
	return packet << x;
}

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::ServerCommand& command)
{
	int x;
	packet >> x;
	command = static_cast<sflcars::utility::network::ServerCommand>(x);
	return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::ClientCommand& command)
{
	int x = static_cast<int>(command);
	return packet << x;
}

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::ClientCommand& command)
{
	int x;
	packet >> x;
	command = static_cast<sflcars::utility::network::ClientCommand>(x);
	return packet;
}