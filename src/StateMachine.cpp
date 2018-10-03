/*
 * StateMachine.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */
#include "StateMachine.hpp"
#include "stm32l0xx.h"
#include "pinout_definitions.hpp"
 RealTimeClock StateMachine::AlarmClock;
 State StateMachine::CurrentState;
 Signal StateMachine::NextSignal;
 Button StateMachine::Buttons;

void StateMachine::Init(){
	transition(&Standby_state);
	//AlarmClock.Init(&CurrentState);
	//AlarmClock.AlarmA.set(0,0,8);
	Buttons.Init(&SetNextSignal);
}


void StateMachine::Update(){
if(NextSignal==SIG_NONE){
	return;
}
//Debouncing the buttons by using a small delay, and then reenabling the interrupt routines
//It would be much cleaner to use a timer for this, but Im getting fed up with these buttons.
if(NextSignal==SIG_BUTTON_1_UP||NextSignal==SIG_BUTTON_1_DN){
	HAL_Delay(5);
	Buttons.Enable(BUTTON_1_ITn);
}else if(NextSignal==SIG_BUTTON_2_UP||NextSignal==SIG_BUTTON_2_DN){
	HAL_Delay(5);
	Buttons.Enable(BUTTON_2_ITn);
}
//a temporary signal container needs to be created here to be able to set the NextSignal to NONE,
//because the handling of the current state can take a long time, and if an interrupt sets the signal, it would be owerwritten.
//
Signal temporarySignal=NextSignal;
NextSignal=SIG_NONE;
CurrentState(temporarySignal);
}
 void StateMachine::SetNextSignal(Signal s){
	 NextSignal=s;
 }




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
	}
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
