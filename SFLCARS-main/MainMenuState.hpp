#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "AppState.hpp"

#include <Bar.hpp>
#include <TextBar.hpp>
#include <Button.hpp>

class AppEngine;

class MainMenuState : public AppState
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
	sf::Sound sound;
	sf::SoundBuffer buffer;
};

#endif // !MAIN_MENU_STATE_HPP
