#include "AppEngine.hpp"
#include "MainMenuState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"
#include "AlarmEditState.hpp"
#include "StandbyState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	toMessageSendState,
	toIntercomState,
	toAlarmEditState,
	toStandbyState,
	Quit,
};

void MainMenuState::Init(AppEngine* app_)
{
	std::cout << "Initialising MainMenuState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(800, 600));
	sflcars::Layout* layout = display->getLayout();

	topbar = new sflcars::TextBar("Main Menu");
	toSendMessageState = new sflcars::Button("Send Message");
	toIntercomState = new sflcars::Button("Intercom");
	toAlarmEditState = new sflcars::Button("Alarms");
	toStandbyState = new sflcars::Button("StandbyState");
	quitButton = new sflcars::Button("Quit");
	bottombar = new sflcars::Bar;

	layout->add(topbar, 10);
	layout->add(toSendMessageState, Callbacks::toMessageSendState);
	layout->add(toIntercomState, Callbacks::toIntercomState);
	layout->add(toAlarmEditState, Callbacks::toAlarmEditState);
	layout->add(toStandbyState, Callbacks::toStandbyState);
	layout->add(quitButton, Callbacks::Quit);
	layout->add(bottombar);

	buffer.loadFromFile("./resources/sounds/initialising.ogg");
	sound.setBuffer(buffer);

	sound.play();

	std::cout << "MainMenuState ready." << std::endl;
}

void MainMenuState::Cleanup()
{
	std::cout << "Cleaning up MainMenuState." << std::endl;

	delete display;

	std::cout << "Cleaned up MainMenuState." << std::endl;
}

void MainMenuState::Pause()
{
	std::cout << "MainMenuState paused." << std::endl;
}

void MainMenuState::Resume()
{
	std::cout << "MainMenuState resumed." << std::endl;
}

void MainMenuState::HandleEvents()
{
	sflcars::DisplayEvent event = display->HandleEvents();

	if (event.event.type == sf::Event::EventType::Closed)
		app->Quit();

	switch (event.elementCallbackID)
	{
	case Callbacks::toMessageSendState:
		app->PushState(new MessageSendState);
		break;
	case Callbacks::toIntercomState:
		app->PushState(new IntercomState);
		break;
	case Callbacks::toAlarmEditState:
		app->PushState(new AlarmEditState);
		break;
	case Callbacks::toStandbyState:
		app->ChangeState(new StandbyState);
		return;
	case Callbacks::Quit:
		app->Quit();
		return;
	default:
		break;
	}
}

void MainMenuState::Update()
{
	display->Update();
}

void MainMenuState::Draw()
{
	display->clear();
	display->DrawLayout();
	display->display();
}

