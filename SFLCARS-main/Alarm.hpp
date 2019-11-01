#ifndef ALARM_HPP
#define ALARM_HPP

#include <string>
#include <ctime>

class Alarm
{
public:
	std::string name;
	std::string soundName;

	time_t date;
	
	// saves the alarm to name file
	bool save();
	// loads the alarm from name file
	bool load(const std::string& name);

private:
	// how many times has the alarm been snoozed?
	int snoozeCounter = 0;
};

#endif // !ALARM_HPP