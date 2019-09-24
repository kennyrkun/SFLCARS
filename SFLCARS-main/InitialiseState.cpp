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

	Draw();

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
}

void InitialiseState::Update()
{
	// we want to draw first
	static int failedConnectionAttempts = 0;
	static bool connectedToServer = false;

	if (app->listener.connectToServer(app->settings.server.serverIpAddress, app->settings.server.serverPort))
	{
		std::cout << "successfully established connection to server." << std::endl;

		sf::Packet packet;
		packet << "connectionRequested";

		if (connectedToServer)
		{
			NetworkEvent event;
			app->listener.pollNetworkEvent(event);

			if (event.packet.getDataSize() > 0)
			{
				std::string command;
				event.packet >> command;

				std::cout << "command: " << command << std::endl;

				if (command == "connectionAccepted")
				{
					app->ChangeState(new LoginState);
					return;
				}
				else
				{
					// TODO: eventually do try to reconnect
					std::cerr << "connection not accepted: (" << command << ")" << std::endl;
					abort();
				}
			}
		}
	}
	else
	{
		std::cerr << "failed to connect to server (" << failedConnectionAttempts << ")" << std::endl;
		app->settings.offline = true;
		failedConnectionAttempts++;
	}

	display->Update();
}

void InitialiseState::Draw()
{
	display->Draw();
}

