#include "AppEngine.hpp"
#include "StandbyState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"
#include "AlarmState.hpp"
#include "Alarm.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

namespace fs = std::experimental::filesystem;

void StandbyState::Init(AppEngine* app_)
{
	std::cout << "Initialising StandbyState" << std::endl;

	app = app_;

	buffer.loadFromFile("./resources/sounds/initialising.ogg");
	sound.setBuffer(buffer);

	sound.play();

	std::cout << "loading alarms" << std::endl;

	for (auto& alarmname : getObjectsAtPath("./sflcars/alarms/", fs::file_type::regular))
	{
		Alarm alarm;
		alarm.load(alarmname);

		time_t timeNow = time(0);

		// difference in seconds between now and the date of the alarm
		time_t timeDifference = timeNow - alarm.date;

		alarmTimes.emplace(alarm.name, timeNow);
	}

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
	std::cout << "StandbyState resumed." << std::endl;
}

void StandbyState::HandleEvents()
{
	sflcars::DisplayEvent event = display->HandleEvents();

	if (event.event.type == sf::Event::EventType::Closed)
		app->Quit();

	switch (event.elementCallbackID)
	{
	default:
		break;
	}
}

void StandbyState::Update()
{
	for (auto& time : alarmTimes)
	{
		if (timer.getElapsedTime().asSeconds() > time.second)
		{
			Alarm alarm;
			alarm.load(time.first);
			app->ChangeState(new AlarmState(alarm));
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
