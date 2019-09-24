#include "AppEngine.hpp"
#include "MainMenuState.hpp"
#include "MessageSendState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	toMessageSendState,
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
	quitButton = new sflcars::Button("Quit");
	bottombar = new sflcars::Bar;

	layout->add(topbar, 10);
	layout->add(toSendMessageState, Callbacks::toMessageSendState);
	layout->add(quitButton, Callbacks::Quit);
	layout->add(bottombar);

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
	display->Draw();
}

