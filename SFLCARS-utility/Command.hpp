#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <SFML/Network.hpp>

namespace sflcars
{
namespace utility
{
namespace network
{

enum Command
{
	None,
	Login,
	LoginSuccess,
	LoginFailure,
	Logout,
	Shutdown,
	ShuttingDown,
	Disconnect,
	Disconnected,
	Connect,
	ConnectionRequested,
	ConnectionAccepted,
	ConnectionRejected,
	Ping,
	Pong,
	SendMessage,
	DeliverMessage,
	MessageSent,
	MessageRecipientInvalid,
	MessageFailedToSend,
	ListClients,
	ClientList,
	Version,
	StartIntercomToClient,
	EndIntercomToClient,
	StartIntercomToAll,
	EndIntercomToAll,
	IntercomData,
};

enum SubCommand
{
	MyVersion,
	YourVersion,
	Login1,
	Login2,
	Login3,
	Login4,
	Login5,
	DuplicateClient,

};

}
}
}

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::Command& command);

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::Command& command);

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::SubCommand& command);

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::SubCommand& command);

#endif // !COMMANDS_HPP
