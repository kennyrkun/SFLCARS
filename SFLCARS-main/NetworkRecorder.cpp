#include "NetworkRecorder.hpp"

#include <Command.hpp>

// Constructor
// \param host Remote host to which send the recording data
// \param port Port of the remote host
NetworkRecorder::NetworkRecorder(sf::TcpSocket* socket) : socket(socket)
{
}

// Destructor
// \see SoundRecorder::~SoundRecorder()
NetworkRecorder::~NetworkRecorder()
{
	// Make sure to stop the recording thread
	stop();
}

// \see SoundRecorder::onProcessSamples
bool NetworkRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	// Pack the audio samples into a network packet
	sf::Packet packet;
	packet << sflcars::utility::network::Command::IntercomDataSend;
	packet << audioData;
	packet.append(samples, sampleCount * sizeof(sf::Int16));

	// Send the audio packet to the server
	return socket->send(packet) == sf::Socket::Done;
}

// \see SoundRecorder::onStop
void NetworkRecorder::onStop()
{
	// Send a "end-of-stream" packet
	sf::Packet packet;
	packet << sflcars::utility::network::Command::EndIntercomToClient;
	packet << endOfStream;
	socket->send(packet);

	// Close the socket
	socket->disconnect();
}
