#include "Utility.hpp"

#include <random>

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
}

}
