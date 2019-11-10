#ifndef ALARM_STATE_HPP
#define ALARM_STATE_HPP

#include "AppState.hpp"
#include "Alarm.hpp"

#include <Date.hpp>
#include <Time.hpp>

#include <Bar.hpp>
#include <TextBar.hpp>
#include <InputBox.hpp>
#include <Button.hpp>
#include <String.hpp>

class AlarmEditState : public AppState
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
	sflcars::InputBox* name;

	sflcars::InputBox* hour;
	sflcars::InputBox* minute;
	sflcars::InputBox* second;

	sflcars::InputBox* day;
	sflcars::InputBox* month;
	sflcars::InputBox* year;

	sflcars::utility::Time time;
	sflcars::utility::Date date;
};

#endif // !ALARM_STATE_HPP
