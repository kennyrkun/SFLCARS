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

	bool clientAuthenticated = false;
	bool elevatedPrivileges = false;
};

#endif // !CLIENT_HPP
