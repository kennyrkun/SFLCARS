#ifndef SFLCARS_UTILITY_HPP
#define SFLCARS_UTILITY_HPP

#include <string>
#include <ctime>

namespace sflcars
{

namespace utility
{
	size_t getRandomNumber(size_t min, size_t max);

	std::string convertToTimestamp(const time_t& time);
}

}

#endif // !SFLCARS_UTILITY_HPP
