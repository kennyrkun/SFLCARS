#include "Time.hpp"

namespace sflcars
{
namespace utility
{

	// TODO: go to top or bottom of time when cap is reached
	// but make sure to keep track of the difference in seconds

void Time::up(Unit unit)
{
	switch (unit)
	{
	case Unit::Hour:
		if (hour < 23)
		{
			hour++;
			time += 3600;
		}
		break;
	case Unit::Minute:
		if (minute < 59)
		{
			minute++;
			time += 60;
		}
		break;
	case Unit::Second:
		if (second < 59)
		{
			second++;
			time += 1;
		}
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
		if (hour > 0)
		{
			hour--;
			time -= 3600;
		}
		break;
	case Unit::Minute:
		if (minute > 0)
		{
			minute--;
			time -= 60;
		}
		break;
	case Unit::Second:
		if (second > 0)
		{
			second--;
			time -= 1;
		}
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
