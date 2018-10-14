/*
 * StateMachine.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */
#include "StateMachine.hpp"
#include "stm32l0xx.h"
#include "pinout_definitions.hpp"
#include <string>
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_nucleo_32.h"

 RealTimeClock StateMachine::AlarmClock;
 State StateMachine::CurrentState=&Standby_state;
 Signal StateMachine::NextSignal;
 Button StateMachine::Buttons;
 Thermometer StateMachine::thermometer;
 Display  StateMachine::display;
void StateMachine::Init(){
	CurrentState=&Standby_state;
	AlarmClock.Init(&SetNextSignal);
	//AlarmClock.AlarmA.set(0,0,8);
	Buttons.Init(&SetNextSignal);
	display.Init();
	display.Enable();
	display.Print("aa");
}


void StateMachine::Update(){
if(NextSignal==SIG_NONE){

		    HAL_Delay(100);
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
volatile uint16_t measurement;
volatile uint16_t temp;
	switch(s){

	case SIG_ENTRY:
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2);
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN3);
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		 /* Disable GPIOs clock */
		 __HAL_RCC_GPIOA_CLK_DISABLE();
		 __HAL_RCC_GPIOB_CLK_DISABLE();
		 /* Enter Stop Mode */
		 HAL_SuspendTick();
		 HAL_RCC_DeInit();
		 HAL_DeInit();
		HAL_PWR_EnterSTANDBYMode();
		break;
	case SIG_ALARM_A:
		//AlarmClock.AlarmA.set(0,0,1);
		measurement=thermometer.measure();
		temp=(measurement-1228)*100/(1544-1228);
		char buffer[20];
		itoa(temp,buffer,10);   // here 2 means binary
	    display.Print(buffer);
		break;
	case SIG_BUTTON_1_DN:
	case SIG_BUTTON_2_DN:
		transition(ButtonDown_state);
		break;
	}
}
void StateMachine::BattCheck_state(Signal s){
switch(s){
	case SIG_ENTRY:
		display.Print("bc");
		AlarmClock.AlarmA.set(0,0,4);
		break;
	case SIG_ALARM_A:
		transition(Standby_state);
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
	case SIG_ENTRY:
		display.Print("bd");
		AlarmClock.AlarmA.set(0,0,2);
		break;
	case SIG_ALARM_A: //the button is being pushed down for more than a 2 secs
		transition(TemperatureSet_state);
		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:
	case SIG_BUTTON_2_UP: //The button was released before the threshold time
		transition(BattCheck_state);
		break;
	case SIG_EXIT:
		AlarmClock.AlarmA.deactivate();
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
	case SIG_ENTRY:
display.Print("ts");
		break;
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
