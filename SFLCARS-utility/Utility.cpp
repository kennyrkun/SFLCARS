#include "Utility.hpp"

#include <random>
#include <string>

namespace sflcars
{

namespace utility
{
	size_t getRandomNumber(size_t min, size_t max)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

		return dist(rng);
	}

	std::string convertToTimestamp(const time_t& time)
	{
		time_t $time = time;

		int seconds = $time % 60;
		$time /= 60;

		int minutes = $time % 60;
		$time /= 60;

		int hours = $time % 24;
		$time /= 24;

		std::string seconds_s(std::to_string(seconds));
		std::string minutes_s(std::to_string(minutes));
		std::string hours_s(std::to_string(hours));

		if (seconds < 10)
			seconds_s.insert(0, "0");

		if (minutes < 10)
			minutes_s.insert(0, "0");

		if (hours < 10)
			hours_s.insert(0, "0");

		return (hours_s + ":" + minutes_s + ":" + seconds_s);
	}
}

}
