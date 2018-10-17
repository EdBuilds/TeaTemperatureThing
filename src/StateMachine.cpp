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
#include "Tunes.hpp"
 RealTimeClock StateMachine::AlarmClock;
 State StateMachine::CurrentState=&Standby_state;
 Signal StateMachine::NextSignal;
 Button StateMachine::Buttons;
 Thermometer StateMachine::thermometer;
 Buzzer StateMachine::buzzer;
 Display  StateMachine::display;

const EepromItem<setpointData> StateMachine::Setpoint;

 etl::queue<Signal,20> StateMachine::SignalContainer;
void StateMachine::Init(bool WakeupRun){
		CurrentState=&Standby_state;
	AlarmClock.Init(&SetNextSignal);
	Buttons.Init(&SetNextSignal);
	buzzer.Init();
	display.Init();
	display.Print("aa");
	//AlarmClock.AlarmA.set(0,0,0,10);
	//display.Enable();
	if(WakeupRun){ //the mcu has been woken up from standby,
		//and the button down callback needs to be called manually
		//detect which button has been pressed
	if(Buttons.read(Button_1)==GPIO_PIN_SET){
		SetNextSignal(SIG_BUTTON_1_DN);
	}else if(Buttons.read(Button_2)==GPIO_PIN_SET){
		SetNextSignal(SIG_BUTTON_2_DN);
	}else{
		//this happens only when the button has been released before the readout.
		//In this case Currently I'm going to ignore it.
	}

	}




}


void StateMachine::Update(){
if(	SignalContainer.empty()){
	//there is nothing to do currently, entering stop mode
	 //HAL_SuspendTick();
	//HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
	 //HAL_ResumeTick();
	return;
}
Signal NextSignal=SignalContainer.front();

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

CurrentState(NextSignal);
SignalContainer.pop();
}
 void StateMachine::SetNextSignal(Signal s){
	 SignalContainer.push(s);
 }

 void StateMachine::transition(State NewState){
	 if(CurrentState!=NULL){
		 CurrentState(SIG_EXIT);
	 }
CurrentState=NewState;
CurrentState(SIG_ENTRY);
 }

void StateMachine::Standby_state(Signal s){
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
		AlarmClock.AlarmB.deactivate();
		display.Print("bc");
		AlarmClock.AlarmA.set(0,0,1,0);
		break;
	case SIG_ALARM_A:
		transition(Alarm_state);
		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:
	case SIG_BUTTON_2_DN:
		transition(ButtonDown_state);
		break;
}
}
void StateMachine::ButtonDown_state(Signal s){
switch(s){
	case SIG_ENTRY:
		AlarmClock.AlarmA.deactivate();
		AlarmClock.AlarmA.set(0,0,2,0);
		break;
	case SIG_ALARM_A: //the button is being pushed down for more than a 2 secs
		transition(Alarm_state);
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
int16_t measurement;
	case SIG_ENTRY:
		display.Enable();
		AlarmClock.AlarmB.set(0,CYCLE_TIMEOUT,0,0);
		measurement=(thermometer.measure()-1228)*100/(1544-1228);
		display.Print(measurement);
		if(measurement>Setpoint.Read()+3){
			transition(Cooling_state);
		}else{
			AlarmClock.AlarmA.set(0,0,2,0);
		}
		break;
	case SIG_ALARM_A:
		measurement=(thermometer.measure()-1228)*100/(1544-1228);
		display.Print(measurement);
		if(measurement>Setpoint.Read()+3){
			transition(Cooling_state);
		}else{
			AlarmClock.AlarmA.set(0,0,2,0);
		}
		break;
	case SIG_ALARM_B:
		transition(Standby_state);
		break;
	case SIG_BUTTON_1_DN:
	case SIG_BUTTON_2_DN:
		transition(ButtonDown_state);
		break;
	case SIG_BUTTON_2_UP:
	case SIG_BUTTON_1_UP:
		break;
}
}
void StateMachine::Cooling_state(Signal s){
switch(s){
uint16_t measurement;
	case SIG_ENTRY:
		measurement=(thermometer.measure()-1228)*100/(1544-1228);
		display.Print(measurement);
		if(measurement<Setpoint.Read()){
			transition(Alarm_state);
		}else{
			AlarmClock.AlarmA.set(0,0,2,0);
		}
		break;
	case SIG_ALARM_A:
		measurement=(thermometer.measure()-1228)*100/(1544-1228);
		display.Print(measurement);
		if(measurement<Setpoint.Read()){
			transition(Alarm_state);
		}else{
			AlarmClock.AlarmA.set(0,0,2,0);
		}
		break;
	case SIG_ALARM_B:
		transition(Standby_state);
		break;
	case SIG_BUTTON_1_DN:
	case SIG_BUTTON_2_DN:
		transition(ButtonDown_state);
		break;
	case SIG_BUTTON_2_UP:
	case SIG_BUTTON_1_UP:
		break;
}
}
void StateMachine::Alarm_state(Signal s){
static int LoopCount;
static int TuneIndex;
static bool TuneRunning;
switch(s){
	case SIG_ENTRY:
		LoopCount=0;
		TuneIndex=0;
		TuneRunning=false;
		AlarmClock.AlarmB.deactivate();
		AlarmClock.AlarmA.deactivate();
//		AlarmClock.AlarmA.set(0,0,0,10);
//		break;
	case SIG_ALARM_A:
		if(TuneIndex>=20){
			if(LoopCount>=3){
				transition(Standby_state);
				return;
			}else{
				++LoopCount;
				TuneIndex=0;
			}

		}

		if(!TuneRunning){
		AlarmClock.AlarmA.set(0,0,
				BasicTune[TuneIndex].onSeconds,
				BasicTune[TuneIndex].onSubseconds);
			buzzer.setFrequency(BasicTune[TuneIndex].frequecy);
			buzzer.start();
			TuneRunning=true;
		}else{
		AlarmClock.AlarmA.set(0,0,
				BasicTune[TuneIndex].offSeconds,
				BasicTune[TuneIndex].offSubseconds);
			buzzer.stop();
			TuneRunning=false;
			TuneIndex++;
		}
		break;
	case SIG_BUTTON_1_UP:
	case SIG_BUTTON_2_UP:
			transition(Standby_state);
		break;
	case SIG_EXIT:
		AlarmClock.AlarmA.deactivate();
		AlarmClock.AlarmB.deactivate();
			buzzer.stop();
		break;
}
}
void StateMachine::TemperatureSet_state(Signal s){
static bool DisplayOn=true;
switch(s){
	case SIG_ENTRY:
AlarmClock.AlarmA.deactivate();
AlarmClock.AlarmB.deactivate();
AlarmClock.AlarmB.set(0,0,5,0);
AlarmClock.AlarmA.set(0,0,0,128);

display.Print(Setpoint.Read());
DisplayOn=true;
display.Enable();
		break;
	case SIG_ALARM_A:
		if(DisplayOn){
			display.Disable();
			DisplayOn=false;
		}else{
			display.Enable();
			DisplayOn=true;
		}
AlarmClock.AlarmA.set(0,0,0,128);
		break;
	case SIG_ALARM_B:
		transition(BattCheck_state);
		break;
	case SIG_BUTTON_1_UP:
AlarmClock.AlarmA.deactivate();
AlarmClock.AlarmB.deactivate();

Setpoint.Write(Setpoint.Read()+1);
display.Print(Setpoint.Read());
DisplayOn=true;
display.Enable();
AlarmClock.AlarmA.set(0,0,0,128);
AlarmClock.AlarmB.set(0,0,5,0);
		break;
	case SIG_BUTTON_2_UP:
AlarmClock.AlarmA.deactivate();
AlarmClock.AlarmB.deactivate();

Setpoint.Write(Setpoint.Read()-1);
display.Print(Setpoint.Read());
DisplayOn=true;
display.Enable();
AlarmClock.AlarmA.set(0,0,0,128);

AlarmClock.AlarmB.set(0,0,5,0);
		break;
	case SIG_EXIT:
AlarmClock.AlarmA.deactivate();
AlarmClock.AlarmB.deactivate();
		break;
}
}
