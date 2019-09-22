#ifndef LOGIN_STATE_HPP
#define LOGIN_STATE_HPP

#include "AppState.hpp"

#include <Bar.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <TextBar.hpp>

class AppEngine;

class LoginState : public AppState
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

		sflcars::InputBox* usernameBox;
		sflcars::InputBox* passwordBox;
		sflcars::Button* submitButton;
		sflcars::Button* quitButton;
		sflcars::TextBar* topbar;
		sflcars::Bar* bottombar;
	};

	Interface* interface;

	std::string username;
	std::string password;
};

#endif // !LOGIN_STATE_HPP
