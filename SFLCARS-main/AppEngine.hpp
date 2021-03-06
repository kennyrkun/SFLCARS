#ifndef APP_ENGINE_HPP
#define APP_ENGINE_HPP

#include "Listener.hpp"
#include "UserAccountManager.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <vector>
#include <string>

class AppState;

struct AppSettings
{
	std::string version = "0.1-19w38a";
	std::string title = "SFLCARS " + version;
	bool vsync = true;
	bool debug = true;
	bool console = false;
	bool useAnimations = true;
	float animationScale = 1;
	int maxfps = 60;

	int timezoneOffset = -6;
	// TODO: this
	//bool use24HourTime = false;

	struct Server
	{
		enum class NetworkOptions
		{
			Offline,
			Local,
			Public,
		} networkType = NetworkOptions::Offline;

		sf::IpAddress serverIpAddress = sf::IpAddress::LocalHost;
		unsigned short serverPort = 12345;

		bool currentlyConnected = false;
	} server;

	struct CommandLineArguments
	{
		int argc;
		char** argv;
	} launchOptions;
};

class AppEngine
{
public:
	void Init(AppSettings settings_);
	void Cleanup();

	// Note: code after these functions is still executed.
	void ChangeState(AppState* state);
	void PushState(AppState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool isRunning() { return running; }
	void Quit();

	AppSettings settings;

	Listener listener;
	UserAccountManager uam;

	std::vector<AppState*> states;
	std::vector<sf::Event> events;

private:
	bool running;
};

#endif // !APP_ENGINE_HPP
