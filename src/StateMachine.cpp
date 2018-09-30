/*
 * StateMachine.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */
#include "StateMachine.hpp"
 RealTimeClock StateMachine::AlarmClock;
 State StateMachine::CurrentState;
void StateMachine::Init(){
	CurrentState = &State1;
	AlarmClock.Init(&CurrentState);
	AlarmClock.AlarmA.set(0,0,8);
}
void StateMachine::State1(Signal s){
	s;
	s++;
	CurrentState = &StateMachine::State2;
	AlarmClock.AlarmA.set(0,0,8);
}
void StateMachine::State2(Signal s){
	s;
	s++;
}
