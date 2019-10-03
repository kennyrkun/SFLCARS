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

	intercomFailBuffer.loadFromFile("./resources/sounds/fail2.ogg");
	intercomFail.setBuffer(intercomFailBuffer);

	app->listener.send(net::ServerCommand::ListClients);

	std::cout << "IntercomState ready." << std::endl;
}

void IntercomState::Cleanup()
{
	std::cout << "Cleaning up IntercomState." << std::endl;

	clients.clear();

	if (transmitting)
	{
		transmitting = false;
		intercomEnd.play();

		if (recorder)
		{
			recorder->stop();
			delete recorder;
		}
	}

	delete display;

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
			std::cout << "elementcallbackid: " << event.elementCallbackID << std::endl;

			if (event.elementCallbackID == Callbacks::AllClients)
			{
				if (!transmitting)
					app->listener.send(net::ServerCommand::StartIntercomToAll);
				else
					std::cerr << "already transmitting" << std::endl;
			}
			else
			{
				// if the client id matches the callback id
				if (clients.find(event.elementCallbackID) != clients.end())
				{
					// second is bool, isActive
					if (clients[event.elementCallbackID].second)
					{
						// NetworkRecorder::onStop notifies the server of the end in transmission
						recorder->stop();
						transmitting = false;
						clients[event.elementCallbackID].second = false;
						intercomEnd.play();
						delete recorder;
					}
					else
					{
						std::cout << "sending request to initiate intercom with client" << std::endl;
						// a request to start an intercom with client id
						sf::Packet packet;
						packet << net::ServerCommand::StartIntercomToClient;
						packet << event.elementCallbackID;

						app->listener.send(packet);
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

	switch (event.command)
	{
	case net::ClientCommand::ClientList:
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
					std::string name = temp;

					id = temp.substr(0, temp.find_first_of(';'));
					std::cout << "id: " << id << std::endl;

					name.erase(name.size() - 1, name.size());
					name.erase(0, name.find_last_of(';') + 1);
					std::cout << "name: " << name << std::endl;

					sflcars::Button* button = new sflcars::Button(id, sf::Keyboard::Key::Num1);
					display->getLayout()->add(button, iterations);

					clients[iterations] = std::pair<int, bool>(std::stoi(id), false);
				}

				iterations++;
			}

			std::cout << "ClientList: " << total << std::endl;
		}
		break;
	}
	case net::ClientCommand::IntercomReady:
	{
		bool toAll = false;

		event.packet >> toAll;

		if (toAll)
		{
			intercomAllStart.play();

			/*
			recorder = new NetworkRecorder(&app->listener.socket);
			recorder->start();
			transmitting = true;
			*/
		}
		else
		{
			int clientID;
			event.packet >> clientID;

			recorder = new NetworkRecorder(&app->listener.socket);
			recorder->start();
			transmitting = true;
			clients[clientID].second = true;
			intercomStart.play();

			std::cout << "intercom is ready" << std::endl;
			break;
		}
	}
	case net::ClientCommand::IntercomDataReceive:
	{
		//std::cout << "processing intercom data" << std::endl;
		//intercomStreams[client->id]->receiveStep(packet);

		break;
	}
	case net::ClientCommand::IntercomNotReady:
	{
		intercomFail.play();
		break;
	}
	default:
		// print the contents of the packet
		break;
	}

	display->Update();
}

void IntercomState::Draw()
{
	display->Draw();
}
