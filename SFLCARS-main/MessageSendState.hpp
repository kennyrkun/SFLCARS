#ifndef MESSAGE_SEND_STATE_HPP
#define MESSAGE_SEND_STATE_HPP

#include "AppState.hpp"

#include <Bar.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <TextBar.hpp>

class AppEngine;

class MessageSendState : public AppState
{
public:
	void Init(AppEngine* app_);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

	const bool connectionRequired = true;

private:
	sflcars::InputBox* destinationBox;
	sflcars::InputBox* messageBox;
	sflcars::Button* submitButton;
	sflcars::Button* quitButton;
	sflcars::TextBar* topbar;
	sflcars::Bar* bottombar;
};

#endif // !MESSAGE_SEND_STATE_HPP
