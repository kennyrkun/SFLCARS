#include "AppEngine.hpp"
#include "IntercomState.hpp"

#include <Display.hpp>
#include <Layout.hpp>

#include <iostream>

enum Callbacks
{
	AllClients,
	Quit
};

void IntercomState::Init(AppEngine* app_)
{
	std::cout << "Initialising IntercomState" << std::endl;

	app = app_;

	if (display != nullptr)
	{
		delete display;
		display = nullptr;
	}

	display = new sflcars::Display(sf::VideoMode(800, 600));

	topbar = new sflcars::TextBar("Intercom");
	allClientsButton = new sflcars::Button("All Clients");
	quitButton = new sflcars::Button("Quit", sf::Keyboard::Key::Escape);
	bottombar = new sflcars::Bar;

	sflcars::Layout& layout = *display->getLayout();

	layout.add(topbar);
	layout.add(allClientsButton, Callbacks::AllClients);
	layout.add(quitButton, Callbacks::Quit);
	layout.add(bottombar);

	intercomAllBuffer.loadFromFile("./resources/sounds/transmission/bosun_whistle.ogg");
	intercomAllStart.setBuffer(intercomAllBuffer);

	intercomStartBuffer.loadFromFile("./resources/sounds/transmission/start_transmit2.ogg");
	intercomStart.setBuffer(intercomStartBuffer);

	intercomEndBuffer.loadFromFile("./resources/sounds/transmission/end_transmit2.ogg");
	intercomEnd.setBuffer(intercomEndBuffer);

	recorder = new NetworkRecorder(&app->listener.socket);

	app->listener.send(net::Command::ListClients);

	std::cout << "MessageSendState ready." << std::endl;
}

void IntercomState::Cleanup()
{
	std::cout << "Cleaning up IntercomState." << std::endl;

	delete display;
	delete recorder;

	std::cout << "Cleaned up IntercomState." << std::endl;
}

void IntercomState::Pause()
{
	std::cout << "IntercomState paused." << std::endl;
}

void IntercomState::Resume()
{
	std::cout << "IntercomState resumed." << std::endl;
}

void IntercomState::HandleEvents()
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
	case Callbacks::Quit:
	{
		app->PopState();
		return;
	}
	default:
	{
		if (event.elementCallbackID != -1)
		{
			if (event.elementCallbackID == Callbacks::AllClients)
				intercomAllStart.play();
			else
			{
				if (clients.find(event.elementCallbackID) != clients.end())
				{
					// second is bool, isActive
					if (clients[event.elementCallbackID].second)
					{
						app->listener.send(net::Command::EndIntercomToClient);
						clients[event.elementCallbackID].second = false;
						intercomEnd.play();
						recorder->stop();
					}
					else
					{
						app->listener.send(net::Command::StartIntercomToClient);
						recorder->start();
						clients[event.elementCallbackID].second = true;
						intercomStart.play();
					}
				}
			}
		}
		break;
	}
	}
}

void IntercomState::Update()
{
	NetworkEvent event;
	app->listener.pollNetworkEvent(event);

	if (event.command != net::Command::None)
	{
		switch (event.command)
		{
		case net::Command::ClientList:
		{
			if (event.packet.getDataSize() > 0)
			{
				std::string total;

				int iterations = 100; // make sure we're after the interface buttons and stuff
				while (!event.packet.endOfPacket())
				{
					std::string temp;
					event.packet >> temp;
					total += ("\n" + temp);

					if (temp != "ClientList:")
					{
						std::string id = temp;
						std::string ip = temp;
						std::string name = temp;

						id = temp.substr(0, temp.find_first_of(';'));
						std::cout << "id: " << id << std::endl;

						ip.erase(0, ip.find_first_of(';') + 1);
						ip.erase(ip.find_first_of(';'), ip.size());
						std::cout << "ip: " << ip << std::endl;

						name.erase(name.size() - 1, name.size());
						name.erase(0, name.find_last_of(';') + 1);
						std::cout << "name: " << name << std::endl;

						sflcars::Button* button = new sflcars::Button(temp, sf::Keyboard::Key::Num1);
						display->getLayout()->add(button, iterations);

						clients[iterations] = std::pair<sf::IpAddress, bool>(sf::IpAddress(ip), false);
					}

					iterations++;
				}

				std::cout << "ClientList: " << total << std::endl;
			}
		}
		default:
			break;
		}
	}
	else
	{
		// print the contents of the packet
	}

	display->Update();
}

void IntercomState::Draw()
{
	display->Draw();
}
