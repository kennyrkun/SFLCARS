#ifndef ALARM_HPP
#define ALARM_HPP

#include <string>
#include <ctime>

class Alarm
{
public:
	std::string name;
	time_t date;
	
	// how many times has the alarm been snoozed?
	int snoozeCounter = 0;
};

#endif // !ALARM_HPP