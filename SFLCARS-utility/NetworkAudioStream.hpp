#ifndef NETWORK_AUDIO_STREAM_HPP
#define NETWORK_AUDIO_STREAM_HPP

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iomanip>
#include <iostream>
#include <iterator>

namespace sflcars
{
namespace utility
{
namespace network
{

const sf::Uint8 audioData = 1;
const sf::Uint8 endOfStream = 2;

// Customized sound stream for acquiring audio data
// from the network
class NetworkAudioStream : public sf::SoundStream
{
public:

	// Default constructor
	NetworkAudioStream();

	// Get audio data from the client until playback is stopped
	void receiveStep(sf::Packet& packet, bool finished = false);

private:
	// see SoundStream::OnGetData
	virtual bool onGetData(sf::SoundStream::Chunk& data);

	// see SoundStream::OnSeek
	virtual void onSeek(sf::Time timeOffset);

	// Member data
	sf::Mutex              m_mutex;
	std::vector<sf::Int16> m_samples;
	std::vector<sf::Int16> m_tempBuffer;
	std::size_t            m_offset;
	bool                   m_hasFinished;
};

}
}
}

#endif // !NETWORK_AUDIO_STREAM_HPP
