/*
 * Alarm.hpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#ifndef INC_REAL_TIME_CLOCK_HPP_
#define INC_REAL_TIME_CLOCK_HPP_
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
	RTC_AlarmTypeDef rtc_alarm_;

	public:
	SignalCallback alarm_callback_;
	Alarm(RTC_AlarmTypeDef alarm_instance, SignalCallback alarm_x_callback) :
			rtc_alarm_(alarm_instance), alarm_callback_(alarm_x_callback) {}
	Alarm(){}
	void Deactivate();
	void Set(uint8_t hours, uint8_t minutes, uint8_t seconds,
			uint16_t sub_seconds);
};

class RealTimeClock {
	public:
	static RTC_HandleTypeDef hrtc_;
	static Alarm alarm_a_;
	static Alarm alarm_b_;
	void Init(SignalCallback alarm_callback);
};

#endif  // INC_REAL_TIME_CLOCK_HPP_
