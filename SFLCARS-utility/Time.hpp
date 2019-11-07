#ifndef SFLCARS_UTILITY_TIME_HPP
#define SFLCARS_UTILITY_TIME_HPP

#include <string>

namespace sflcars
{
namespace utility
{

class Time
{
public:
	enum class Unit
	{
		Hour,
		Minute,
		Second,
	};

	int hour, minute, second;

	void up(Unit unit);
	void down(Unit unit);

	std::string asString();
};

}
}

#endif // !SFLCARS_UTILITY_TIME_HPP
