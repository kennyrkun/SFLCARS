#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>

#include <string>

class Client
{
public:
	std::string name;

	sf::IpAddress ip;
	int id;

	sf::TcpSocket* socket;
};

#endif // !CLIENT_HPP
