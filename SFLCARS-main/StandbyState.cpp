#include "AppEngine.hpp"
#include "StandbyState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"
#include "AlarmState.hpp"
#include "Alarm.hpp"

#include "Utility.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

namespace fs = std::experimental::filesystem;

void StandbyState::Init(AppEngine* app_)
{
	std::cout << "Initialising StandbyState" << std::endl;

	app = app_;

	buffer.loadFromFile("./resources/sounds/powerdown.ogg");
	sound.setBuffer(buffer);
	sound.play();

	loadAlarms();

	std::cout << "StandbyState ready." << std::endl;
}

void StandbyState::Cleanup()
{
	std::cout << "Cleaning up StandbyState." << std::endl;

	std::cout << "Cleaned up StandbyState." << std::endl;
}

void StandbyState::Pause()
{
	std::cout << "StandbyState paused." << std::endl;
}

void StandbyState::Resume()
{
	loadAlarms();

	std::cout << "StandbyState resumed." << std::endl;
}

void StandbyState::HandleEvents()
{
}

void StandbyState::Update()
{
	for (auto& time : alarmTimes)
	{
		if (alarmDifferencetTimer.getElapsedTime().asSeconds() >= time.second)
		{
			Alarm alarm;
			alarm.load(time.first);
			alarmTimes.erase(time.first);
			app->PushState(new AlarmState(alarm));
			break;
		}
	}
}

void StandbyState::Draw()
{
}

std::vector<std::string> StandbyState::getObjectsAtPath(const std::string& s, fs::file_type type)
{
	std::vector<std::string> r;
	for (auto& p : fs::directory_iterator(s))
		if (p.status().type() == type)
			// this cuts out the front part of the path name
			// and just gives us what comes after s
			r.push_back(p.path().string().substr(s.size(), p.path().string().size()));
	return r;
}

void StandbyState::loadAlarms()
{
	alarmTimes.clear();

	std::cout << "loading alarms" << std::endl;

	for (auto& alarmname : getObjectsAtPath("./sflcars/alarms/", fs::file_type::regular))
	{
		std::cout << "loading " << alarmname << std::endl;

		// do not load the file if it is not an alarm file
		if (alarmname.substr(alarmname.length() - 6, alarmname.length()) != ".alarm")
			continue;

		Alarm alarm;
		// substring is everything except .alarm
		alarm.load(alarmname.substr(0, alarmname.length() - 6));

		time_t timeNow = time(0);

		time_t timeDifference = difftime(alarm.date, timeNow);
		std::cout << "timediff: " << timeDifference << std::endl;

		if (timeDifference < 0)
		{
			std::cout << "Alarm date has already passed (" << timeNow << " > " << alarm.date << ")" << std::endl;
			continue;
		}

		std::string time = sflcars::utility::convertToTimestamp(timeDifference);

		std::cout << "alarm should trigger " << time << " from now" << std::endl;

		alarmTimes.emplace(alarm.name, timeDifference);
	}

	std::cout << "loaded " << alarmTimes.size() << " alarms" << std::endl;

	alarmDifferencetTimer.restart();
}
