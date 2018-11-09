/*
 * StateMachine.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */
#include <state_machine.hpp>
#include <tunes.hpp>
#include "inc/pinout_definitions.hpp"
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
//#include "stm32l0xx.h"
//#include "stm32l0xx_nucleo_32.h"

RealTimeClock StateMachine::AlarmClock;
State StateMachine::current_state_ = &StandbyState;
Signal StateMachine::next_signal_;
Button StateMachine::buttons_;
Thermometer StateMachine::thermometer_;
Buzzer StateMachine::buzzer_;
Display StateMachine::display_;
const EepromItem<SetpointData> StateMachine::setpoint_;

etl::queue<Signal, 20> StateMachine::signal_container_;
void StateMachine::Init(bool wakeup_run) {
	current_state_ = &StandbyState;
	AlarmClock.Init(&SetNextSignal);
	buttons_.Init(&SetNextSignal);
	buzzer_.Init();
	display_.Init();
	display_.Print("aa");

	if (wakeup_run) { //the mcu has been woken up from standby,
		//and the button down callback needs to be called manually
		//detect which button has been pressed
		if (buttons_.Read(BUTTON_1) == GPIO_PIN_SET) {
			SetNextSignal(SIG_BUTTON_1_DN);
		} else if (buttons_.Read(BUTTON_2) == GPIO_PIN_SET) {
			SetNextSignal(SIG_BUTTON_2_DN);
		} else {
			//this happens only when the button has been released before the readout.
			//In this case Currently I'm going to ignore it.
		}

	}

}

void StateMachine::Update() {
	if (signal_container_.empty()) {
		//there is nothing to do currently, entering stop mode
		//HAL_SuspendTick();
		//HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
		//HAL_ResumeTick();
		return;
	}
	Signal next_signal = signal_container_.front();

//Debouncing the buttons by using a small delay, and then reenabling the interrupt routines
//It would be much cleaner to use a timer for this, but Im getting fed up with these buttons.
	if (next_signal == SIG_BUTTON_1_UP || next_signal == SIG_BUTTON_1_DN) {
		HAL_Delay(5);
		buttons_.Enable(BUTTON_1_ITn);
	} else if (next_signal == SIG_BUTTON_2_UP || next_signal == SIG_BUTTON_2_DN) {
		HAL_Delay(5);
		buttons_.Enable(BUTTON_2_ITn);
	}
//a temporary signal container needs to be created here to be able to set the NextSignal to NONE,
//because the handling of the current state can take a long time, and if an interrupt sets the signal, it would be owerwritten.
//

	current_state_(next_signal);
	signal_container_.pop();
}
void StateMachine::SetNextSignal(Signal s) {
	signal_container_.push(s);
}

void StateMachine::Transition(State new_state) {
	if (current_state_ != NULL) {
		current_state_(SIG_EXIT);
	}
	current_state_ = new_state;
	current_state_(SIG_ENTRY);
}

void StateMachine::StandbyState(Signal s) {
	switch (s) {

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
		Transition(ButtonDownState);
		break;
	}
}
void StateMachine::BattCheckState(Signal s) {
	switch (s) {
	case SIG_ENTRY:
		AlarmClock.alarm_b_.Deactivate();
		//TODO implement battery checking here
		display_.Print("bc");
		display_.Enable();
		AlarmClock.alarm_a_.Set(0, 0, 1, 0);
		break;
	case SIG_ALARM_A:
		Transition(WarmingState);
		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:
	case SIG_BUTTON_2_DN:
		Transition(ButtonDownState);
		break;
	}
}
void StateMachine::ButtonDownState(Signal s) {
	switch (s) {
	case SIG_ENTRY:
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_a_.Set(0, 0, 2, 0);
		break;
	case SIG_ALARM_A: //the button is being pushed down for more than a 2 secs
		Transition(TemperatureSetState);
		break;
	case SIG_ALARM_B:

		break;
	case SIG_BUTTON_1_DN:

		break;
	case SIG_BUTTON_1_UP:
	case SIG_BUTTON_2_UP: //The button was released before the threshold time
		Transition(BattCheckState);
		break;
	case SIG_EXIT:
		AlarmClock.alarm_a_.Deactivate();
		break;
	}
}
void StateMachine::WarmingState(Signal s) {
	switch (s) {
	int16_t measurement;
case SIG_ENTRY:
	display_.Enable();
	AlarmClock.alarm_b_.Set(0, CYCLE_TIMEOUT, 0, 0);
	measurement = (thermometer_.Measure() - 1228) * 100 / (1544 - 1228);
	display_.Print(measurement);
	if (measurement > setpoint_.Read() + 3) {
		Transition(CoolingState);
	} else {
		AlarmClock.alarm_a_.Set(0, 0, 2, 0);
	}
	break;
case SIG_ALARM_A:
	measurement = (thermometer_.Measure() - 1228) * 100 / (1544 - 1228);
	display_.Print(measurement);
	if (measurement > setpoint_.Read() + 3) {
		Transition(CoolingState);
	} else {
		AlarmClock.alarm_a_.Set(0, 0, 2, 0);
	}
	break;
case SIG_ALARM_B:
	Transition(StandbyState);
	break;
case SIG_BUTTON_1_DN:
case SIG_BUTTON_2_DN:
	Transition(ButtonDownState);
	break;
case SIG_BUTTON_2_UP:
case SIG_BUTTON_1_UP:
	break;
	}
}
void StateMachine::CoolingState(Signal s) {
	switch (s) {
	uint16_t measurement;
case SIG_ENTRY:
	measurement = (thermometer_.Measure() - 1228) * 100 / (1544 - 1228);
	display_.Print(measurement);
	if (measurement < setpoint_.Read()) {
		Transition(AlarmState);
	} else {
		AlarmClock.alarm_a_.Set(0, 0, 2, 0);
	}
	break;
case SIG_ALARM_A:
	measurement = (thermometer_.Measure() - 1228) * 100 / (1544 - 1228);
	display_.Print(measurement);
	if (measurement < setpoint_.Read()) {
		Transition(AlarmState);
	} else {
		AlarmClock.alarm_a_.Set(0, 0, 2, 0);
	}
	break;
case SIG_ALARM_B:
	Transition(StandbyState);
	break;
case SIG_BUTTON_1_DN:
case SIG_BUTTON_2_DN:
	Transition(ButtonDownState);
	break;
case SIG_BUTTON_2_UP:
case SIG_BUTTON_1_UP:
	break;
	}
}
void StateMachine::AlarmState(Signal s) {
	static int loop_count;
	static int tune_index;
	static bool tune_running;
	static bool display_on;
	uint16_t measurement;
	switch (s) {
	case SIG_ENTRY:
		loop_count = 0;
		tune_index = 0;
		tune_running = false;
		AlarmClock.alarm_b_.Deactivate();
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_b_.Set(0, 0, 0, TIMEBASE * 4);
		display_.Print(setpoint_.Read());
		display_on = true;
		measurement = (thermometer_.Measure() - 1228) * 100 / (1544 - 1228);
		display_.Print(measurement);
		display_.Enable();
	case SIG_ALARM_A:
		if (tune_index >= 20) {
			if (loop_count >= 3) {
				Transition(StandbyState);
				return;
			} else {
				++loop_count;
				tune_index = 0;
			}

		}

		if (!tune_running) {
			AlarmClock.alarm_a_.Set(0, 0, BasicTune[tune_index].on_seconds,
					BasicTune[tune_index].on_sub_seconds);
			buzzer_.SetFrequency(BasicTune[tune_index].frequecy);
			buzzer_.Start();
			tune_running = true;
		} else {
			AlarmClock.alarm_a_.Set(0, 0, BasicTune[tune_index].off_seconds,
					BasicTune[tune_index].off_sub_seconds);
			buzzer_.Stop();
			tune_running = false;
			tune_index++;
		}
		break;
	case SIG_ALARM_B:
		if (display_on) {
			display_.Disable();
			display_on = false;
		} else {
			measurement = (thermometer_.Measure() - 1228) * 100 / (1544 - 1228);
			display_.Print(measurement);
			display_.Enable();
			display_on = true;
		}
		AlarmClock.alarm_b_.Set(0, 0, 0, TIMEBASE * 4);
		break;
	case SIG_BUTTON_1_UP:
	case SIG_BUTTON_2_UP:
		Transition(StandbyState);
		break;
	case SIG_EXIT:
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_b_.Deactivate();
		buzzer_.Stop();
		break;
	}
}
void StateMachine::TemperatureSetState(Signal s) {
	static bool display_on = true;
	switch (s) {
	case SIG_ENTRY:
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_b_.Deactivate();
		AlarmClock.alarm_b_.Set(0, 0, 5, 0);
		AlarmClock.alarm_a_.Set(0, 0, 0, 128);

		display_.Print(setpoint_.Read());
		display_on = true;
		display_.Enable();
		break;
	case SIG_ALARM_A:
		if (display_on) {
			display_.Disable();
			display_on = false;
		} else {
			display_.Enable();
			display_on = true;
		}
		AlarmClock.alarm_a_.Set(0, 0, 0, 128);
		break;
	case SIG_ALARM_B:
		Transition(BattCheckState);
		break;
	case SIG_BUTTON_1_UP:
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_b_.Deactivate();

		setpoint_.Write(setpoint_.Read() + 1);
		display_.Print(setpoint_.Read());
		display_on = true;
		display_.Enable();
		AlarmClock.alarm_a_.Set(0, 0, 0, 128);
		AlarmClock.alarm_b_.Set(0, 0, 5, 0);
		break;
	case SIG_BUTTON_2_UP:
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_b_.Deactivate();

		setpoint_.Write(setpoint_.Read() - 1);
		display_.Print(setpoint_.Read());
		display_on = true;
		display_.Enable();
		AlarmClock.alarm_a_.Set(0, 0, 0, 128);

		AlarmClock.alarm_b_.Set(0, 0, 5, 0);
		break;
	case SIG_EXIT:
		AlarmClock.alarm_a_.Deactivate();
		AlarmClock.alarm_b_.Deactivate();
		break;
	}
}
