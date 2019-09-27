#ifndef INTERCOM_STATE_HPP
#define INTERCOM_STATE_HPP

#include "AppState.hpp"
#include "NetworkRecorder.hpp"

#include <Bar.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <TextBar.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Audio.hpp>

#include <map>

class AppEngine;

class IntercomState : public AppState
{
public:
	void Init(AppEngine* app_);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

private:
	sflcars::TextBar* topbar;
	sflcars::Button* allClientsButton;
	sflcars::Button* quitButton;
	sflcars::Bar* bottombar;

	// callback id, client id, transmitting
	std::map<int, std::pair<int, bool>> clients;

	sf::Sound intercomStart;
	sf::Sound intercomEnd;
	sf::Sound intercomAllStart;
	sf::SoundBuffer intercomAllBuffer;
	sf::SoundBuffer intercomStartBuffer;
	sf::SoundBuffer intercomEndBuffer;

	NetworkRecorder* recorder;

	bool transmitting = false;
};

#endif // !INTERCOM_STATE_HPP
