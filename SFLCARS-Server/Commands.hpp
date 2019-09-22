#ifndef COMMANDS_HPP
#define COMMANDS_HPP

enum class COmmands
{
	Login,
	Logout,
	Disconnect,
	Disconnected,
	Connect,
	ConnectionAccepted,
	ConnectionRejected,
	Ping,
	Pong,
	SendMessage,
	DeliverMessage,
	ListClients,
};

#endif // !COMMANDS_HPP
