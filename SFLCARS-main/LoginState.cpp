#include "AppEngine.hpp"
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

void LoginState::Init(AppEngine* app_)
{
	std::cout << "Initialising LoginState" << std::endl;

	app = app_;

	display = new sflcars::Display(sf::VideoMode(300, 310), sf::Vector2i(0, 0));

	interface = new Interface;

	display->addElement(interface->topbar);
	display->addElement(interface->usernameBox, Callbacks::UsernameBox);
	display->addElement(interface->passwordBox, Callbacks::PasswordBox);
	display->addElement(interface->submitButton, Callbacks::SubmitButton);
	display->addElement(interface->quitButton, sflcars::Display::Layout::Horizontal, Callbacks::QuitButton);
	display->addElement(interface->bottombar);

	std::cout << "LoginState ready." << std::endl;
}

void LoginState::Cleanup()
{
	std::cout << "Cleaning up LoginState." << std::endl;

	delete interface;

	std::cout << "Cleaned up LoginState." << std::endl;
}

void LoginState::Pause()
{
	std::cout << "LoginState paused." << std::endl;
}

void LoginState::Resume()
{
	std::cout << "LoginState resumed." << std::endl;
}

void LoginState::HandleEvents()
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

void LoginState::Update()
{
	NetworkEvent event;
	app->listener.pollNetworkEvent(event);

	if (event.receivedTime != 0)
	{
		std::string total;

		while (!event.packet.endOfPacket())
		{
			event.packet << "\n" + total;
		}

		std::cout << "server: " << total << std::endl;
	}

	display->Update();
}

void LoginState::Draw()
{
	display->Draw();
}

LoginState::Interface::Interface()
{
	topbar = new sflcars::TextBar("Login");
	usernameBox = new sflcars::InputBox;
	passwordBox = new sflcars::InputBox;
	submitButton = new sflcars::Button("Submit", sf::Keyboard::Key::Return);
	quitButton = new sflcars::Button("Quit", sf::Keyboard::Key::Escape);
	bottombar = new sflcars::Bar;
}

LoginState::Interface::~Interface()
{
	delete topbar;
	delete usernameBox;
	delete passwordBox;
	delete submitButton;
	delete quitButton;
	delete bottombar;
}
