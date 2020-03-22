#include "AppEngine.hpp"
#include "AlarmState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	EndAlarm,
	SnoozeAlarm,
	Quit,
};

AlarmState::AlarmState(Alarm alarm) : alarm(alarm)
{
}

void AlarmState::Init(AppEngine* app_)
{
	std::cout << "Initialising AlarmState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(800, 600));
	sflcars::Layout* layout = display->getLayout();

	layout->add(new sflcars::TextBar(alarm.name));

	{
		struct tm timeInfo;

#if defined(_WIN32)
		localtime_s(&timeInfo, &alarm.date);
#elif defined(__linux__)
		localtime_r(&alarm.date, &timeInfo);
#else
		timeInfo = localtime(&alarm.date);
#endif

		std::string timestamp = std::to_string(timeInfo.tm_hour) + ":" + std::to_string(timeInfo.tm_min);

		layout->add(time = new sflcars::String(timestamp));
		time->setCharacterSize(128);
	}

	layout->add(new sflcars::Button("End"), Callbacks::EndAlarm);
	layout->add(new sflcars::Button("Snooze"), sflcars::Layout::Alignment::Horizontal, Callbacks::SnoozeAlarm);
	layout->add(new sflcars::Bar);

	buffer.loadFromFile("./resources/sounds/alarm/" + alarm.soundName + ".wav");
	blinkPeriod = buffer.getDuration().asSeconds();
	sound.setBuffer(buffer);
	sound.setLoop(true);

	sound.play();

	std::cout << "AlarmState ready." << std::endl;
}

void AlarmState::Cleanup()
{
	std::cout << "Cleaning up AlarmState." << std::endl;

	delete display;

	std::cout << "Cleaned up AlarmState." << std::endl;
}

void AlarmState::Pause()
{
	std::cout << "AlarmState paused." << std::endl;
}

void AlarmState::Resume()
{
	std::cout << "AlarmState resumed." << std::endl;
}

void AlarmState::HandleEvents()
{
	sflcars::DisplayEvent event = display->HandleEvents();

	if (event.event.type == sf::Event::EventType::Closed)
		app->Quit();

	switch (event.elementCallbackID)
	{
	case Callbacks::EndAlarm:
		endAlarm();
		break;
	case Callbacks::SnoozeAlarm:
		snoozeAlarm();
		break;
	case Callbacks::Quit:
		app->Quit();
		break;
	default:
		break;
	}
}

void AlarmState::Update()
{
	display->Update();
}

void AlarmState::Draw()
{
	display->clear();

	float timer = timeTimer.getElapsedTime().asSeconds();
	if (timer >= blinkPeriod)
		timeTimer.restart();

	// Updating in the drawing method, deal with it
	//sf::Color color = Theme::label.textColor;
	sf::Color color = sf::Color::White;
	color.a = 255 - (255 * timer / blinkPeriod);
	time->setFillColor(color);

	display->DrawLayout();
	display->display();
}

void AlarmState::endAlarm()
{
	sound.stop();
	app->PopState();
}

void AlarmState::snoozeAlarm()
{
	sound.stop();
	alarm.snooze();
	app->PopState();
}

