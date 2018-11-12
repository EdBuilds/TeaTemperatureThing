/*
 * StateMachine.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */

#ifndef INC_STATE_MACHINE_HPP_
#define INC_STATE_MACHINE_HPP_

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

/**
 * @brief this class executes all the behaviour and logic of the device and keeps track of the current state
 */
class StateMachine {
	public:
	static RealTimeClock AlarmClock;

	void Init(bool wakeup_run);
	void Update();

	private:
	static const EepromItem<HeaderData> header_;
	static const EepromItem<SetpointData> setpoint_;
	static const EepromItem<CalibrationData> calibration_data_;
	static etl::queue<Signal, 20> signal_container_;
	static Thermometer thermometer_;
	static Display display_;
	static Buzzer buzzer_;
	static State current_state_;
	static Signal next_signal_;
	static Button buttons_;
	static void SetNextSignal(Signal s);
	// State functions
	static void Transition(State new_state);
	static void StandbyState(Signal s);
	static void BattCheckState(Signal s);
	static void ButtonDownState(Signal s);
	static void WarmingState(Signal s);
	static void CoolingState(Signal s);
	static void AlarmState(Signal s);
	static void TemperatureSetState(Signal s);
};

#endif  // INC_STATE_MACHINE_HPP_
