#include "AppEngine.hpp"
#include "InitialiseState.hpp"
#include "LoginState.hpp"

#include <Display.hpp>

#include <iostream>

enum Callbacks
{
	UsernameBox,
	PasswordBox,
	SubmitButton,
	QuitButton
};

void InitialiseState::Init(AppEngine* app_)
{
	std::cout << "Initialising InitialiseState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(800, 600));

	interface = new Interface;

	display->addElement(interface->topbar);
	display->addElement(interface->continueButton, Callbacks::SubmitButton);
	display->addElement(interface->bottombar);

	std::cout << "InitialiseState ready." << std::endl;
}

void InitialiseState::Cleanup()
{
	std::cout << "Cleaning up InitialiseState." << std::endl;

//	delete interface;
	delete display;

	std::cout << "Cleaned up InitialiseState." << std::endl;
}

void InitialiseState::Pause()
{
	std::cout << "InitialiseState paused." << std::endl;
}

void InitialiseState::Resume()
{
	std::cout << "InitialiseState resumed." << std::endl;
}

void InitialiseState::HandleEvents()
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

	switch (event.elementCallbackID)
	{
	case Callbacks::SubmitButton:
	{
		sf::Packet packet;
		packet << "ping";
		app->listener.sendToServer(packet);
		break;
	}
	default:
		break;
	}
}

void InitialiseState::Update()
{
	// we want to draw first
	static int updates = 0;
	static bool connectedToServer = false;

	if (updates >= 1)
	{
		if (!connectedToServer)
		{
			if (!app->listener.connectToServer(sf::IpAddress::LocalHost, 12345))
			{
				std::cerr << "failed to connect to server (" << updates << ")" << std::endl;
				app->settings.offline = true;
			}
			else
			{
				std::cout << "connected to server" << std::endl;
				app->ChangeState(new LoginState);
				return;
			}
		}
		else
		{
			app->ChangeState(new LoginState);
			return;
		}
	}

	display->Update();

	updates++;
}

void InitialiseState::Draw()
{
	display->Draw();
}

InitialiseState::Interface::Interface()
{
	topbar = new sflcars::TextBar("SFLCARS");
	continueButton = new sflcars::String("Initialising");
	bottombar = new sflcars::Bar;
}

InitialiseState::Interface::~Interface()
{
	delete topbar;
	topbar = nullptr;
	delete continueButton;
	continueButton = nullptr;
	delete bottombar;
	bottombar = nullptr;
}
