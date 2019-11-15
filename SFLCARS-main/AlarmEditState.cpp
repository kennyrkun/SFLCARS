#include "AppEngine.hpp"
#include "AlarmEditState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	HourUp,
	HourDown,
	MinuteUp,
	MinuteDown,
	SecondUp,
	SecondDown,
	DayUp,
	DayDown,
	MonthUp,
	MonthDown,
	YearUp,
	YearDown,

	Save,
	Quit,
};

AlarmEditState::AlarmEditState()
{
	// do nothing
	time.time = std::time(0);
	name = new sflcars::InputBox;
	name->setText("New Alarm");
}

AlarmEditState::AlarmEditState(Alarm alarm)
{
	std::cout << "editing " << alarm.name << std::endl;
	time.time = alarm.date;
	name = new sflcars::InputBox;
	name->setText(alarm.name);
}

void AlarmEditState::Init(AppEngine* app_)
{
	std::cout << "Initialising AlarmEditState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(800, 600));
	sflcars::Layout* layout = display->getLayout();

	layout->add(new sflcars::TextBar("Edit Alarm"));

	layout->add(name);

	layout->add(new sflcars::Button("up"), Callbacks::HourUp);
	layout->add(hour = new sflcars::InputBox, sflcars::Layout::Alignment::Horizontal);
	layout->add(new sflcars::Button("down"), sflcars::Layout::Alignment::Horizontal, Callbacks::HourDown);

	layout->add(new sflcars::Button("up"), Callbacks::MinuteUp);
	layout->add(minute = new sflcars::InputBox, sflcars::Layout::Alignment::Horizontal);
	layout->add(new sflcars::Button("down"), sflcars::Layout::Alignment::Horizontal, Callbacks::MinuteDown);

	layout->add(new sflcars::Button("up"), Callbacks::SecondUp);
	layout->add(second = new sflcars::InputBox, sflcars::Layout::Alignment::Horizontal);
	layout->add(new sflcars::Button("down"), sflcars::Layout::Alignment::Horizontal, Callbacks::SecondDown);

	layout->add(new sflcars::Button("up"));
	layout->add(new sflcars::Button("up"), sflcars::Layout::Alignment::Horizontal);
	layout->add(new sflcars::Button("up"), sflcars::Layout::Alignment::Horizontal);
	layout->add(year = new sflcars::InputBox);
	layout->add(month = new sflcars::InputBox, sflcars::Layout::Alignment::Horizontal);
	layout->add(day = new sflcars::InputBox, sflcars::Layout::Alignment::Horizontal);
	layout->add(new sflcars::Button("down"));
	layout->add(new sflcars::Button("down"), sflcars::Layout::Alignment::Horizontal);
	layout->add(new sflcars::Button("down"), sflcars::Layout::Alignment::Horizontal);

	layout->add(new sflcars::Button("Save"), Callbacks::Save);
	layout->add(new sflcars::Button("Quit"), sflcars::Layout::Alignment::Horizontal, Callbacks::Quit);

	
	layout->add(new sflcars::Bar);

	time.time += app->settings.timezoneOffset * 3600;

	std::time_t $time = time.time;
	int seconds = $time % 60;
	time.second = seconds;
	$time /= 60;
	int minutes = $time % 60;
	time.minute = minutes;
	$time /= 60;
	int hours = $time % 24;
	time.hour = hours;
	$time /= 24;

	second->setText(std::to_string(seconds));
	minute->setText(std::to_string(minutes));
	hour->setText(std::to_string(hours));

	if (layout->getSize().x > display->getSize().x)
		display->setSize(sf::Vector2u(layout->getSize().x, display->getSize().y));

	if (layout->getSize().y > display->getSize().y)
		display->setSize(sf::Vector2u(display->getSize().x, layout->getSize().y));

	std::cout << "AlarmEditState ready." << std::endl;
}

void AlarmEditState::Cleanup()
{
	std::cout << "Cleaning up AlarmEditState." << std::endl;

	delete display;

	std::cout << "Cleaned up AlarmEditState." << std::endl;
}

void AlarmEditState::Pause()
{
	std::cout << "AlarmEditState paused." << std::endl;
}

void AlarmEditState::Resume()
{
	std::cout << "AlarmEditState resumed." << std::endl;
}

void AlarmEditState::HandleEvents()
{
	sflcars::DisplayEvent event = display->HandleEvents();

	if (event.event.type == sf::Event::EventType::Closed)
		app->Quit();

	switch (event.elementCallbackID)
	{
		case Callbacks::HourUp:
		{
			time.up(sflcars::utility::Time::Unit::Hour);
			hour->setText(std::to_string(time.hour));
			break;
		}
		case Callbacks::HourDown:
		{
			time.down(sflcars::utility::Time::Unit::Hour);
			hour->setText(std::to_string(time.hour));
			break;
		}
		case Callbacks::MinuteUp:
		{
			time.up(sflcars::utility::Time::Unit::Minute);
			minute->setText(std::to_string(time.minute));
			break;
		}
		case Callbacks::MinuteDown:
		{
			time.down(sflcars::utility::Time::Unit::Minute);
			minute->setText(std::to_string(time.minute));
			break;
		}
		case Callbacks::SecondUp:
		{
			time.up(sflcars::utility::Time::Unit::Second);
			second->setText(std::to_string(time.second)); 
			break;
		}
		case Callbacks::SecondDown:
		{
			time.down(sflcars::utility::Time::Unit::Second);
			second->setText(std::to_string(time.second));
			break;
		}
		case Callbacks::DayUp:
		case Callbacks::DayDown:
		case Callbacks::MonthUp:
		case Callbacks::MonthDown:
		case Callbacks::YearUp:
		case Callbacks::YearDown:
		case Callbacks::Save:
		{
			Alarm alarm;
			alarm.name = name->getText();
			alarm.date = time.time - (app->settings.timezoneOffset * 3600);
			alarm.save();
			break;
		}
		case Callbacks::Quit:
			app->PopState();
			return;
	default:
		break;
	}
}

void AlarmEditState::Update()
{
	display->Update();
}

void AlarmEditState::Draw()
{
	display->clear();
	display->DrawLayout();
	display->display();
}
