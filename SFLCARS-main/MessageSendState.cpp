#include "AppEngine.hpp"
#include "MessageSendState.hpp"

#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	Login,
	Quit
};

void MessageSendState::Init(AppEngine* app_)
{
	std::cout << "Initialising MessageSendState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(300, 310), sf::Vector2i(0, 0));

	interface = new Interface;

	display->addElement(interface->topbar);
	display->addElement(interface->usernameBox);
	display->addElement(interface->passwordBox);
	display->addElement(interface->submitButton, Callbacks::Login);
	display->addElement(interface->quitButton, sflcars::Display::Layout::Horizontal, Callbacks::Quit);
	display->addElement(interface->bottombar);

	std::cout << "MessageSendState ready." << std::endl;
}

void MessageSendState::Cleanup()
{
	std::cout << "Cleaning up MessageSendState." << std::endl;

	delete interface;

	std::cout << "Cleaned up MessageSendState." << std::endl;
}

void MessageSendState::Pause()
{
	std::cout << "MessageSendState paused." << std::endl;
}

void MessageSendState::Resume()
{
	std::cout << "MessageSendState resumed." << std::endl;
}

void MessageSendState::HandleEvents()
{
	sflcars::DisplayEvent event = display->HandleEvents();

	if (event.event.type == sf::Event::EventType::Closed)
		app->Quit();
	else if (event.event.type == sf::Event::EventType::KeyPressed)
	{
		if (event.event.key.code == sf::Keyboard::Key::Tilde)
		{
			app->settings.debug = !app->settings.debug;

			std::cout << "cl_debug set to " + std::to_string(app->settings.debug) << std::endl;
		}
	}
}

void MessageSendState::Update()
{
	display->Update();
}

void MessageSendState::Draw()
{
	display->Draw();
}

MessageSendState::Interface::Interface()
{
	topbar = new sflcars::TextBar("Login");
	usernameBox = new sflcars::InputBox;
	passwordBox = new sflcars::InputBox;
	submitButton = new sflcars::Button("Submit", sf::Keyboard::Key::Return);
	quitButton = new sflcars::Button("Quit", sf::Keyboard::Key::Escape);
	bottombar = new sflcars::Bar;
}

MessageSendState::Interface::~Interface()
{
	delete topbar;
	delete usernameBox;
	delete passwordBox;
	delete submitButton;
	delete quitButton;
	delete bottombar;
}
