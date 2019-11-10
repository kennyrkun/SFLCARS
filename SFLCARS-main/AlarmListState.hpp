#ifndef ALARM_LIST_STATE_HPP
#define ALARM_LIST_STATE_HPP

#include "AppState.hpp"

#include "Alarm.hpp"

#include <filesystem>
#include <vector>

namespace fs = std::experimental::filesystem;

class AlarmListState : public AppState
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
	// alarm id, alarm
	std::map<int, Alarm> alarms;
	// button id, alarm id
	std::map<int, int> alarmDeleteButtons;

	std::vector<std::string> getObjectsAtPath(const std::string& s, fs::file_type type);

	void buildMenu();
};

#endif // !ALARM_LIST_STATE_HPP
