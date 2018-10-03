/*
 * StateMachine.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */

#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_
#include "pinout_definitions.hpp"
#include "RealTimeClock.hpp"
#include "Button_driver.hpp"
typedef void(*State)(Signal);
class StateMachine {
    public:
	 static RealTimeClock AlarmClock;

	void Init();
	void Update();
    private:
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

#endif /* STATEMACHINE_HPP_ */
