#ifndef NETWORK_RECORDER_HPP
#define NETWORK_RECORDER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

// TODO: stop using these
const sf::Uint8 audioData = 1;
const sf::Uint8 endOfStream = 2;

// Specialization of audio recorder for sending recorded audio
// data through the network
class NetworkRecorder : public sf::SoundRecorder
{
public:
	// Constructor
	NetworkRecorder(sf::TcpSocket* socket);

	// Destructor
	// \see SoundRecorder::~SoundRecorder()
	~NetworkRecorder();

private:
	// \see SoundRecorder::onProcessSamples
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);

	// \see SoundRecorder::onStop
	virtual void onStop();

	sf::TcpSocket* socket;
};

#endif // !NETWORK_RECORDER_HPP
