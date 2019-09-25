#ifndef COMMANDS_HPP
#define COMMANDS_HPP

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

#endif // !COMMANDS_HPP
