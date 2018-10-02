/*
 * StateMachine.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */
#include "StateMachine.hpp"
#include "stm32l0xx.h"
 RealTimeClock StateMachine::AlarmClock;
 State StateMachine::CurrentState;
 Button StateMachine::Buttons;
void StateMachine::Init(){
	transition(&Standby_state);
	AlarmClock.Init(&CurrentState);
	//AlarmClock.AlarmA.set(0,0,8);
	Buttons.Init(&CurrentState);
}
/**
 *
 * @param NewState
 */
 void StateMachine::transition(State NewState){
	 if(CurrentState!=NULL){
		 CurrentState(SIG_EXIT);
	 }
CurrentState=NewState;
CurrentState(SIG_ENTRY);
 }

void StateMachine::Standby_state(Signal s){
	static int i=0;
	switch(s){

		case SIG_ALARM_A:

			break;
		case SIG_ALARM_B:

			break;
		case SIG_BUTTON_1_DN:
			i--;
			break;
		case SIG_BUTTON_1_UP:

			i++;
			break;
		case SIG_BUTTON_2_DN:

			break;
		case SIG_BUTTON_2_UP:

			break;
		default:
			i+=100;
	}
	HAL_Delay(i);
}
void StateMachine::BattCheck_state(Signal s){
switch(s){
	case SIG_ALARM_A:

		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:

		break;
	case SIG_BUTTON_2_DN:

		break;
	case SIG_BUTTON_2_UP:

		break;
}
}
void StateMachine::ButtonDown_state(Signal s){
switch(s){
	case SIG_ALARM_A:

		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:

		break;
	case SIG_BUTTON_2_DN:

		break;
	case SIG_BUTTON_2_UP:

		break;
}
}
void StateMachine::Warming_state(Signal s){
switch(s){
	case SIG_ALARM_A:

		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:

		break;
	case SIG_BUTTON_2_DN:

		break;
	case SIG_BUTTON_2_UP:

		break;
}
}
void StateMachine::Cooling_state(Signal s){
switch(s){
	case SIG_ALARM_A:

		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:

		break;
	case SIG_BUTTON_2_DN:

		break;
	case SIG_BUTTON_2_UP:

		break;
}
}
void StateMachine::Alarm_state(Signal s){
switch(s){
	case SIG_ALARM_A:

		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:

		break;
	case SIG_BUTTON_2_DN:

		break;
	case SIG_BUTTON_2_UP:

		break;
}
}
void StateMachine::TemperatureSet_state(Signal s){
switch(s){
	case SIG_ALARM_A:

		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:

		break;
	case SIG_BUTTON_2_DN:

		break;
	case SIG_BUTTON_2_UP:

		break;
}
}
