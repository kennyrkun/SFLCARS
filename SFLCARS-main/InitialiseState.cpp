#include "AppEngine.hpp"
#include "InitialiseState.hpp"
#include "LoginState.hpp"

#include <Layout.hpp>
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
	sflcars::Layout* layout = display->getLayout();

	topbar = new sflcars::TextBar("SFLCARS");
	text = new sflcars::String("Initialising");
	bottombar = new sflcars::Bar;

	layout->add(topbar, 10);
	layout->add(text, Callbacks::SubmitButton);
	layout->add(bottombar);

	std::cout << "InitialiseState ready." << std::endl;
}

void InitialiseState::Cleanup()
{
	std::cout << "Cleaning up InitialiseState." << std::endl;

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
			if (!app->listener.connectToServer(app->settings.server.serverIpAddress, app->settings.server.serverPort))
			{
				std::cerr << "failed to connect to server (" << updates << ")" << std::endl;
				app->settings.offline = true;
			}
			else // success
			{
				std::cout << "connected to server" << std::endl;
				app->ChangeState(new LoginState);
				return;
			}
		}
		else // connected to server
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

