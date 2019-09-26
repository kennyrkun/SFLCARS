#include "Command.hpp"

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::Command& command)
{
	int x = static_cast<int>(command);
	return packet << x;
}

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::Command& command)
{
	int x;
	packet >> x;
	command = static_cast<sflcars::utility::network::Command>(x);
	return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::SubCommand& command)
{
	int x = static_cast<int>(command);
	return packet << x;
}

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::SubCommand& command)
{
	int x;
	packet >> x;
	command = static_cast<sflcars::utility::network::SubCommand>(x);
	return packet;
}