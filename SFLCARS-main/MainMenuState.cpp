#include "AppEngine.hpp"
#include "MainMenuState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	toMessageSendState,
	toIntercomState,
	toAlarmState,
	toStandbyState,
	Quit,
};

void MainMenuState::Init(AppEngine* app_)
{
	std::cout << "Initialising MainMenuState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(800, 600));
	sflcars::Layout* layout = display->getLayout();

	layout->add(new sflcars::TextBar("Main Menu"), 10);
	layout->add(new sflcars::TextBar("Main Menu"), Callbacks::toMessageSendState);
	layout->add(new sflcars::Button("Intercom"), Callbacks::toIntercomState);
	layout->add(new sflcars::Button("Alarms"), Callbacks::Quit);
	layout->add(new sflcars::Button("Standby"), Callbacks::Quit);
	layout->add(new sflcars::Button("Quit"), Callbacks::Quit);
	layout->add(new sflcars::Bar);

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
	case Callbacks::Quit:
		app->Quit();
		break;
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

