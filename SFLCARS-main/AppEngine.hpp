#ifndef APP_ENGINE_HPP
#define APP_ENGINE_HPP

#include "Listener.hpp"

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
	int maxfps = 60;

	bool offline = false;

	struct Server
	{
		sf::IpAddress serverIpAddress = sf::IpAddress::LocalHost;
		unsigned short serverPort = 12345;
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
	AppEngine(AppSettings settings_);
	~AppEngine();

	// Note: code after these functions is still executed.
	void ChangeState(AppState* state);
	void PushState(AppState* state);
	void PopState();
	void PopState(int amount);

	void HandleEvents();
	void Update();
	void Draw();

	bool isRunning() { return running; }
	void Quit();

	std::string title;

	AppSettings settings;

	Listener listener;

	std::vector<AppState*> states;
	std::vector<sf::Event> events;

private:
	bool running;
};

#endif // !APP_ENGINE_HPP
