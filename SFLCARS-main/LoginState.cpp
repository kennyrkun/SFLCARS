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
	sflcars::Layout& layout = *display->getLayout();

	topbar = new sflcars::TextBar("Login");
	usernameBox = new sflcars::InputBox;
	passwordBox = new sflcars::InputBox;
	submitButton = new sflcars::Button("Submit", sf::Keyboard::Key::Return);
	quitButton = new sflcars::Button("Quit", sf::Keyboard::Key::Escape);
	bottombar = new sflcars::Bar;

	layout.add(topbar);
	layout.add(usernameBox, Callbacks::UsernameBox);
	layout.add(passwordBox, Callbacks::PasswordBox);
	layout.add(submitButton, Callbacks::SubmitButton);
	layout.add(quitButton, Callbacks::QuitButton);
	layout.add(bottombar);

	std::cout << "LoginState ready." << std::endl;
}

void LoginState::Cleanup()
{
	std::cout << "Cleaning up LoginState." << std::endl;

	delete display; // TODO: find out if this also cleans up the elements of that are class members

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
		username = usernameBox->getText().toAnsiString();
		password = passwordBox->getText().toAnsiString();

		sf::Packet packet;
		packet << net::Command::Login;
		packet << "step1";
		packet << username;

//		interface->submitButton->disable();

		app->listener.send(packet);
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

	if (event.command != net::Command::None)
	{
		switch (event.command)
		{
		case net::Command::Login:
		{
			std::string loginStep;
			event.packet >> loginStep;

			if (loginStep == "step2")
			{
				std::cout << "we need ot encrypt the rando numbo" << std::endl;

				std::string randoHash;
				event.packet >> randoHash;

				// step 3
				std::string password = passwordBox->getText().toAnsiString();
				std::string passwordHash = sflcars::utility::password::hashString(password);
				std::string superHash = sflcars::utility::password::hashString(passwordHash + randoHash);

				sf::Packet response;
				response << net::Command::Login;
				response << "step4";
				response << username;
				response << randoHash;
				response << superHash;

				app->listener.send(response);
			}
			break;
		}
		case net::Command::LoginSuccess:
		{
			std::cout << "login successful!" << std::endl;
			
			// play initialising sound

			app->ChangeState(new MainMenuState);
			return;
		}
		default:
			std::cerr << "ERROR: this code is unreachable and should never be executed" << std::endl;
			break;
		}
	}

	display->Update();
}

void LoginState::Draw()
{
	display->clear();
	display->DrawLayout();
	display->display();
}
