#ifndef SFLCARS_UTILITY_DATE_HPP
#define SFLCARS_UTILITY_DATE_HPP

#include <string>

namespace sflcars
{
namespace utility
{

class Date
{
public:
	enum class Unit
	{
		Day,
		Month,
		Year,
	};

	int day, month, year;

	void up(Unit unit);
	void down(Unit unit);

	std::string asString();
};

}
}

#endif // !SFLCARS_UTILITY_DATE_HPP
