#include "Date.hpp"

namespace sflcars
{
namespace utility
{

void Date::up(Unit unit)
{
	switch (unit)
	{
	case Date::Unit::Day:
		if (day < 31)
			day++;
		break;
	case Date::Unit::Month:
		if (month < 12)
			month++;
		break;
	case Date::Unit::Year:
		year++;
		break;
	default:
		break;
	}
}

void Date::down(Unit unit)
{
	switch (unit)
	{
	case Date::Unit::Day:
		if (day > 1)
			day--;
		break;
	case Date::Unit::Month:
		if (month > 1)
			month--;
		break;
	case Date::Unit::Year:
		if (year > 1970)
			year--;
		break;
	default:
		break;
	}
}

}
}
