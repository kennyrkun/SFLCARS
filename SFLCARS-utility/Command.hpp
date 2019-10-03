#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/Network.hpp>

namespace sflcars
{
namespace utility
{
namespace network
{

// These are commands sent to the server. (client -> server)
enum class ServerCommand
{
	None,
	Ping,
	Pong,
	Information,
	Login, // TODO: we might want a few more commands for the steps
	Logout,
	Shutdown,
	Disconnecting, // the server acknowledges your departure
	ConnectionRequested,
	SendMessage,
	ReceivedMessage,
	ListClients,
	MyVersionIs,
	WhatIsYourVersion,
	StartIntercomToClient,
	StartIntercomToAll,
	IncomingIntercom,
	EndIntercom,
	ReceiveIntercomData,
	PingAllClients,
	UnknownCommand,
};

// These are commands sent to the client. (server -> client)
enum class ClientCommand
{
	None,
	Ping,
	Pong,
	Information,
	LoginStep, // TODO: probably send login step in information
	LoginSuccess,
	LoginFailure,
	ShuttingDown,
	ConnectionAccepted,
	ConnectionRejected,
	Disconnected,
	DeliverMessage,
	MessageSent,
	MessageDelivered,
	MessageRecipientInvalid,
	MessageFailed,
	ClientList,
	MyVersionIs,
	WhatIsYourVersion,
	IntercomReady,
	IntercomNotReady,
	IntercomRequested,
	IntercomTerminated,
	IntercomDataReceive,
	UnknownCommand,
};

}
}
}

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::ServerCommand& command);

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::ServerCommand& command);

sf::Packet& operator <<(sf::Packet& packet, const sflcars::utility::network::ClientCommand& command);

sf::Packet& operator >>(sf::Packet& packet, sflcars::utility::network::ClientCommand& command);

#endif // !COMMAND_HPP
