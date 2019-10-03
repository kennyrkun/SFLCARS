#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Command.hpp>

#include <SFML/Network.hpp>

#include <ctime>

namespace net = sflcars::utility::network;

class AppEngine;

struct NetworkEvent
{
	net::ClientCommand command;

	time_t receivedTime = 0;
	sf::Packet packet;
};

#endif // !NETWORK_HPP
