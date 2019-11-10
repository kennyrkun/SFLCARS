#ifndef ALARM_STATE_HPP
#define ALARM_STATE_HPP

#include "AppState.hpp"
#include "Alarm.hpp"

#include <Bar.hpp>
#include <TextBar.hpp>
#include <Button.hpp>
#include <String.hpp>

class AppEngine;

class AlarmState : public AppState
{
public:
	AlarmState(Alarm alarm);

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

	Alarm alarm;

	mutable sf::Clock timeTimer;
	float			  blinkPeriod = 5.0f;

	sflcars::String* time;

	void endAlarm();
	void snoozeAlarm();
};

#endif // !ALARM_STATE_HPP
