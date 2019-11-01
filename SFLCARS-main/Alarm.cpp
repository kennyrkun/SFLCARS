#include "Alarm.hpp"

#include <SettingsParser.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

void Alarm::snooze()
{
	// in minutes
	size_t snoozeTime = 5;
	time_t snoozems = snoozeTime * 60000;

	time_t timeNow = time(0);
	time_t newTime = timeNow += snoozems;

	std::cout << "new alarm time is: " << newTime << std::endl;

	save();
}

bool Alarm::save()
{
	if (!fs::exists("./sflcars/alarms/" + name + ".alarm"))
	{
		std::ofstream create("./sflcars/alarms/" + name + ".name", std::ios::out | std::ios::trunc);

		if (!create.is_open())
		{
			std::cout << "failed to create alarm file" << std::endl;
			return false;
		}
	}

	sflcars::utility::SettingsParser alarmParser;

	if (!alarmParser.loadFromFile(("./sflcars/alarms/" + name + ".alarm")))
	{
		std::cout << "failed to open alarm file" << std::endl;
		return false;
	}

	alarmParser.set("name", name);
	alarmParser.set("soundName", soundName);
	alarmParser.set("snoozes", snoozeCounter);
	alarmParser.set("date", date);

	return true;
}

bool Alarm::load(const std::string& name)
{
	if (!fs::exists("./sflcars/alarms/" + name + ".alarm"))
	{
		std::cerr << "alarm file does not exist" << std::endl;
		return false;
	}

	sflcars::utility::SettingsParser alarmParser;

	if (!alarmParser.loadFromFile(("./sflcars/alarms/" + name + ".alarm")))
	{
		std::cout << "failed to open alarm file" << std::endl;
		return false;
	}

	alarmParser.get("name", name);
	alarmParser.get("soundName", soundName);
	alarmParser.get("snoozes", snoozeCounter);
	alarmParser.get("date", date);

	return true;
}
