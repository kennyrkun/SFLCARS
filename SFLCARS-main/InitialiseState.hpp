#ifndef INITIALISE_STATE_HPP
#define INITIALISE_STATE_HPP

#include "AppState.hpp"

#include <Bar.hpp>
#include <Button.hpp>
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
	struct Interface
	{
		Interface();
		~Interface();

		sflcars::TextBar* topbar;
		sflcars::String* continueButton;
		sflcars::Bar* bottombar;
	};

	Interface* interface;
};

#endif // !INITIALISE_STATE_HPP
