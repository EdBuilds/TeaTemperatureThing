/*
 * StateMachine.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */

#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_
#include <inc/button_driver.hpp>
#include <inc/buzzer_driver.hpp>
#include <inc/persistent_storage.hpp>
#include <inc/real_time_clock.hpp>
#include <inc/thermometer_driver.hpp>
#include "inc/pinout_definitions.hpp"
#include "inc/display_driver.hpp"
#include "inc/signal_definition.hpp"
#include "etl/include/etl/queue.h"
#define STATE_BTNDN_DELAY 2
#define CYCLE_TIMEOUT 20

class StateMachine {
public:
	static RealTimeClock AlarmClock;

	void Init(bool WakeupRun);
	void Update();
private:
	static const EepromItem<HeaderData> Header;
	static const EepromItem<setpointData> Setpoint;
	static const EepromItem<calibrationData> CalibrationData;
	static etl::queue<Signal, 20> SignalContainer;
	static Thermometer thermometer;
	static Display display;
	static Buzzer buzzer;
	static State CurrentState;
	static Signal NextSignal;
	static void SetNextSignal(Signal s);

	static void transition(State NewState);
	static void Standby_state(Signal s);
	static void BattCheck_state(Signal s);
	static void ButtonDown_state(Signal s);
	static void Warming_state(Signal s);
	static void Cooling_state(Signal s);
	static void Alarm_state(Signal s);
	static void TemperatureSet_state(Signal s);
	static Button Buttons;
};

#endif /* STATE_MACHINE_HPP_ */
