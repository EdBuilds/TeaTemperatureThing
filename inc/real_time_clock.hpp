/*
 * Alarm.hpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#ifndef REAL_TIME_CLOCK_HPP_
#define REAL_TIME_CLOCK_HPP_
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
#include "inc/signal_definition.hpp"
#ifdef __cplusplus
extern "C" {
#endif
void RTC_IRQHandler(void);
#ifdef __cplusplus
}
#endif
class Alarm {
	RTC_AlarmTypeDef sAlarm;
public:
	SignalCallback AlarmCallback;
	Alarm(RTC_AlarmTypeDef alarmInstance, SignalCallback alarmXCallback) :
			sAlarm(alarmInstance), AlarmCallback(alarmXCallback) {
	}
	Alarm() {
	}
	void deactivate();
	void set(uint8_t hours, uint8_t minutes, uint8_t seconds,
			uint16_t subSeconds);
};

class RealTimeClock {
public:
	static RTC_HandleTypeDef hrtc;
	static Alarm AlarmA;
	static Alarm AlarmB;
	void Init(SignalCallback AlarmCallback);
};

#endif /* REAL_TIME_CLOCK_HPP_ */
