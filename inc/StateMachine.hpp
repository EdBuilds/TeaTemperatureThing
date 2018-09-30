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
class StateMachine {
    public:
	 static RealTimeClock AlarmClock;
	void Init();
    private:
	static State CurrentState;
	 static void State1(Signal s);
	 static void State2(Signal s);
};

#endif /* STATEMACHINE_HPP_ */
