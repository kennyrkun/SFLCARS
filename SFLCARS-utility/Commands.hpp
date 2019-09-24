#ifndef COMMANDS_HPP
#define COMMANDS_HPP

namespace sflcars
{
namespace network
{

enum class Commands
{
	Login,
	Logout,
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
	ListClients,
};

}
}

#endif // !COMMANDS_HPP
