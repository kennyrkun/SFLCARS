#include "NetworkAudioStream.hpp"

namespace sflcars
{
namespace utility
{
namespace network
{

NetworkAudioStream::NetworkAudioStream() : m_offset(0), m_hasFinished(false)
{
	// Set the sound parameters
	initialize(1, 44100);
}

bool NetworkAudioStream::onGetData(sf::SoundStream::Chunk& data)
{
	// We have reached the end of the buffer and all audio data have been played: we can stop playback
	if ((m_offset >= m_samples.size()) && m_hasFinished)
		return false;

	// No new data has arrived since last update: wait until we get some
	while ((m_offset >= m_samples.size()) && !m_hasFinished)
		sf::sleep(sf::milliseconds(10));

	try
	{
		// Copy samples into a local buffer to avoid synchronization problems
		// (don't forget that we run in two separate threads)
		{
			sf::Lock lock(m_mutex);

			// FIXME: this is broken
			m_tempBuffer.assign(m_samples.begin() + m_offset, m_samples.end());
			// FIXME: this is broken
		}

		// Fill audio data to pass to the stream
		data.samples = &m_tempBuffer[0];
		data.sampleCount = m_tempBuffer.size();
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: exception in NetworkAudioStream::onGetData():" << std::endl;
		std::cout << e.what() << std::endl;
		return false;
	}

	// Update the playing offset
	m_offset += m_tempBuffer.size();

	return true;
}

void NetworkAudioStream::onSeek(sf::Time timeOffset)
{
	m_offset = timeOffset.asMilliseconds() * getSampleRate() * getChannelCount() / 1000;
}

void NetworkAudioStream::receiveStep(sf::Packet& packet, bool finished)
{
	// Extract the message ID
	sf::Uint8 id;
	packet >> id;

	std::cout << (int)id << std::endl;

	if (id == audioData)
	{
		// Extract audio samples from the packet, and append it to our samples buffer
		const sf::Int16* samples = reinterpret_cast<const sf::Int16*>(static_cast<const char*>(packet.getData()) + 1);
		std::size_t      sampleCount = (packet.getDataSize() - 1) / sizeof(sf::Int16);

		// Don't forget that the other thread can access the sample array at any time
		// (so we protect any operation on it with the mutex)
		{
			sf::Lock lock(m_mutex);
			std::copy(samples, samples + sampleCount, std::back_inserter(m_samples));
		}
	}
	else if (id == endOfStream || finished)
	{
		// End of stream reached: we stop receiving audio data
		std::cout << "Audio data has been 100% received! and finished" << std::endl;
		m_hasFinished = true;
	}
	else
	{
		// Something's wrong...
		std::cout << "Invalid packet received: " << (int)id << std::endl;
		m_hasFinished = true;
	}
}

}
}
}
