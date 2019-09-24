#include "AppEngine.hpp"
#include "MessageSendState.hpp"

#include <Display.hpp>
#include <Layout.hpp>

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

	if (display != nullptr)
	{
		delete display;
		display = nullptr;
	}

	display = new sflcars::Display(sf::VideoMode(300, 310));

	topbar = new sflcars::TextBar("Send Message");
	destinationBox = new sflcars::InputBox;
	messageBox = new sflcars::InputBox;
	submitButton = new sflcars::Button("Send", sf::Keyboard::Key::Return);
	quitButton = new sflcars::Button("Quit", sf::Keyboard::Key::Escape);
	bottombar = new sflcars::Bar;

	sflcars::Layout& layout = *display->getLayout();

	layout.add(topbar);
	layout.add(destinationBox);
	layout.add(messageBox);
	layout.add(submitButton, Callbacks::Login);
	layout.add(quitButton, sflcars::Layout::Alignment::Horizontal, Callbacks::Quit);
	layout.add(bottombar);

	std::cout << "MessageSendState ready." << std::endl;
}

void MessageSendState::Cleanup()
{
	std::cout << "Cleaning up MessageSendState." << std::endl;

	delete display;

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

	switch (event.elementCallbackID)
	{
	case Callbacks::Login:
	{
		std::string who = destinationBox->getText().toAnsiString();
		std::string what = messageBox->getText().toAnsiString();

		sf::Packet packet;
		packet << "messageSend";
		packet << who;
		packet << what;

		app->listener.send(packet);
		break;
	}
	case Callbacks::Quit:
	{
		app->PopState();
		return;
	}
	default:
		break;
	}
}

void MessageSendState::Update()
{
	NetworkEvent event;
	app->listener.pollNetworkEvent(event);

	if (event.packet.getDataSize() > 0)
	{
		std::string total;

		event.packet >> total;

		if (total == "messageDeliver")
		{
			std::cout << "message recieved" << std::endl;

			std::string from, message;
			event.packet >> from;
			event.packet >> message;

			std::cout << from << ": " << message << std::endl;
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

void MessageSendState::Draw()
{
	display->Draw();
}
