#ifndef STANDBY_STATE_HPP
#define STANDBY_STATE_HPP

#include "AppState.hpp"

#include <SFML/System/Clock.hpp>

#include <Bar.hpp>
#include <TextBar.hpp>
#include <Button.hpp>

#include <filesystem>
#include <vector>

class AppEngine;
class Alarm;

class StandbyState : public AppState
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

	std::vector<std::string> getObjectsAtPath(const std::string& s, std::experimental::filesystem::file_type type);
	std::map<std::string, time_t> alarmTimes;

	sf::Clock timer;
};

#endif // !STANDBY_STATE_HPP
