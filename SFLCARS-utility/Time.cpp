#include "Time.hpp"

namespace sflcars
{
namespace utility
{

void Time::up(Unit unit)
{
	switch (unit)
	{
	case Unit::Hour:
		if (hour < 24)
			hour++;
		break;
	case Unit::Minute:
		if (minute < 60)
			minute++;
		break;
	case Unit::Second:
		if (second < 60)
			second++;
		break;
	default:
		break;
	}
}

void Time::down(Unit unit)
{
	switch (unit)
	{
	case Unit::Hour:
		if (hour > 1)
			hour--;
		break;
	case Unit::Minute:
		if (minute > 1)
			minute--;
		break;
	case Unit::Second:
		if (second > 1)
			second--;
		break;
	default:
		break;
	}
}

std::string Time::asString()
{
	return std::string(std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second));
}

}
}
