#include "AppEngine.hpp"
#include "LoginState.hpp"
#include "MainMenuState.hpp"

#include <Password.hpp>

#include <Display.hpp>
#include <Layout.hpp>

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

	display = new sflcars::Display(sf::VideoMode(300, 310));

	interface = new Interface;

	sflcars::Layout& layout = *display->getLayout();

	layout.add(interface->topbar);
	layout.add(interface->usernameBox, Callbacks::UsernameBox);
	layout.add(interface->passwordBox, Callbacks::PasswordBox);
	layout.add(interface->submitButton, Callbacks::SubmitButton);
	layout.add(interface->quitButton, sflcars::Layout::Alignment::Horizontal, Callbacks::QuitButton);
	layout.add(interface->bottombar);

	std::cout << "LoginState ready." << std::endl;
}

void LoginState::Cleanup()
{
	std::cout << "Cleaning up LoginState." << std::endl;

	delete interface;
	delete display;

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

	switch (event.elementCallbackID)
	{
	case Callbacks::SubmitButton:
	{
		// TODO: hide the boxes while authenticating
		username = interface->usernameBox->getText().toAnsiString();
		password = interface->passwordBox->getText().toAnsiString();

		sf::Packet packet;
		packet << "login";
		packet << "step1";
		packet << username;

//		interface->submitButton->disable();

		app->listener.sendToServer(packet);
		break;
	}
	case Callbacks::QuitButton:
	{
		app->Quit();
		return;
	}
	default:
		break;
	}
}

void LoginState::Update()
{
	NetworkEvent event;
	app->listener.pollNetworkEvent(event);

	if (event.packet.getDataSize() > 0)
	{
		std::string total;

		event.packet >> total;

		if (total == "login")
		{
			std::string loginStep;
			event.packet >> loginStep;

			if (loginStep == "step2")
			{
				std::cout << "we need ot encrypt the rando numbo" << std::endl;

				std::string randoHash;
				event.packet >> randoHash;

				// step 3
				std::string password = interface->passwordBox->getText().toAnsiString();
				std::string passwordHash = sflcars::utility::password::hashString(password);
				std::string superHash = sflcars::utility::password::hashString(passwordHash + randoHash);

				sf::Packet response;
				response << "login";
				response << "step4";
				response << username;
				response << randoHash;
				response << superHash;

				app->listener.sendToServer(response);
			}
		}
		else if (total == "loginSuccess")
		{
			std::cout << "login successful!" << std::endl;

			app->ChangeState(new MainMenuState);
			return;
		}

		while (!event.packet.endOfPacket())
		{
			std::string temp;
			event.packet >> temp;
			total += ("\n" + temp);
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
