#include "AppEngine.hpp"
#include "AlarmListState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"
#include "AlarmEditState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	New = -10,
	Quit,
};

void AlarmListState::Init(AppEngine* app_)
{
	std::cout << "Initialising AlarmListState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(800, 600));

	buildMenu();

	std::cout << "AlarmListState ready." << std::endl;
}

void AlarmListState::Cleanup()
{
	std::cout << "Cleaning up AlarmListState." << std::endl;

	delete display;

	std::cout << "Cleaned up AlarmListState." << std::endl;
}

void AlarmListState::Pause()
{
	std::cout << "AlarmListState paused." << std::endl;
}

void AlarmListState::Resume()
{
	buildMenu();

	std::cout << "AlarmListState resumed." << std::endl;
}

void AlarmListState::HandleEvents()
{
	sflcars::DisplayEvent event = display->HandleEvents();

	if (event.event.type == sf::Event::EventType::Closed)
		app->Quit();

	switch (event.elementCallbackID)
	{
	case Callbacks::New:
		app->PushState(new AlarmEditState);
		return;
	case Callbacks::Quit:
		app->PopState();
		return;
	default:
		break;
	}

	if (event.elementCallbackID >= 0)
	{
		if (event.elementCallbackID < alarms.size())
		{
			app->PushState(new AlarmEditState(alarms[event.elementCallbackID]));
			return;
		}
		else
		{
			std::cout << "deleting alarm " << alarmDeleteButtons[event.elementCallbackID] << " " << alarms[alarmDeleteButtons[event.elementCallbackID]].name << std::endl;

			try
			{
				fs::remove("./sflcars/alarms/" + alarms[alarmDeleteButtons[event.elementCallbackID]].name + ".alarm");
				sf::sleep(sf::milliseconds(100));
				buildMenu();
			}
			catch (const std::exception& e)
			{
				std::cerr << "failed to delete alarm" << std::endl;
			}
		}
	}
}

void AlarmListState::Update()
{
	display->Update();
}

void AlarmListState::Draw()
{
	display->clear();
	display->DrawLayout();
	display->display();
}

std::vector<std::string> AlarmListState::getObjectsAtPath(const std::string& s, fs::file_type type)
{
	std::vector<std::string> r;
	for (auto& p : fs::directory_iterator(s))
		if (p.status().type() == type)
			// this cuts out the front part of the path name
			// and just gives us what comes after s
			r.push_back(p.path().string().substr(s.size(), p.path().string().size()));
	return r;
}

void AlarmListState::buildMenu()
{
	delete display->getLayout();
	sflcars::Layout* layout = new sflcars::Layout(display);
	display->setLayout(layout);

	alarmDeleteButtons.clear();
	alarms.clear();

	layout->add(new sflcars::TextBar("Alarms"));

	layout->add(new sflcars::Button("New"), Callbacks::New);

	std::vector<std::string> ala = getObjectsAtPath("./sflcars/alarms/", fs::file_type::regular);
	for (size_t i = 0; i < ala.size(); i++)
	{
		// do not load the file if it is not an alarm file
		if (ala[i].substr(ala[i].length() - 6, ala[i].length()) != ".alarm")
			continue;

		Alarm alarm;
		alarm.load(ala[i].substr(0, ala[i].length() - 6));
		alarms.emplace(i, alarm);
	}

	int numbersAfterAlarmSize = alarms.size() + 1;
	for (size_t i = 0; i < alarms.size(); i++)
	{
		layout->add(new sflcars::Button(alarms[i].name), i);
		alarmDeleteButtons.emplace(numbersAfterAlarmSize, i);
		layout->add(new sflcars::Button("Delete"), sflcars::Layout::Alignment::Horizontal, numbersAfterAlarmSize);
		numbersAfterAlarmSize++;
	}

	std::cout << "found " << alarms.size() << " alarms" << std::endl;

	layout->add(new sflcars::Button("Quit"), Callbacks::Quit);

	layout->add(new sflcars::Bar);

	if (layout->getSize().x > display->getSize().x)
		display->setSize(sf::Vector2u(layout->getSize().x, display->getSize().y));

	if (layout->getSize().y > display->getSize().y)
		display->setSize(sf::Vector2u(display->getSize().x, layout->getSize().y));
}
