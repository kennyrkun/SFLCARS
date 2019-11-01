#include "AppEngine.hpp"
#include "StandbyState.hpp"
#include "MessageSendState.hpp"
#include "IntercomState.hpp"

#include <Layout.hpp>
#include <Display.hpp>

#include <iostream>

void StandyState::Init(AppEngine* app_)
{
	std::cout << "Initialising StandbyState" << std::endl;

	app = app_;

	buffer.loadFromFile("./resources/sounds/initialising.ogg");
	sound.setBuffer(buffer);

	sound.play();

	std::cout << "StandbyState ready." << std::endl;
}

void StandyState::Cleanup()
{
	std::cout << "Cleaning up StandbyState." << std::endl;

	std::cout << "Cleaned up StandbyState." << std::endl;
}

void StandyState::Pause()
{
	std::cout << "StandbyState paused." << std::endl;
}

void StandyState::Resume()
{
	std::cout << "StandbyState resumed." << std::endl;
}

void StandyState::HandleEvents()
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

void StandyState::Update()
{
}

void StandyState::Draw()
{
}

