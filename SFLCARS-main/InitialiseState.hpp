#ifndef INITIALISE_STATE_HPP
#define INITIALISE_STATE_HPP

#include "AppState.hpp"

#include <Bar.hpp>
#include <TextBar.hpp>
#include <String.hpp>

class AppEngine;

class InitialiseState : public AppState
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
	sflcars::String* text;
	sflcars::Bar* bottombar;

	int failedConnectionAttempts = 0;
	bool connectedToServer = false;
};

#endif // !INITIALISE_STATE_HPP
