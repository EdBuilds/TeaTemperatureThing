/*
 * Alarm.hpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#ifndef ALARM_HPP_
#define ALARM_HPP_
#include "stm32l0xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif
void RTC_IRQHandler(void);
#ifdef __cplusplus
}
#endif

class Alarm{
public:
static RTC_HandleTypeDef hrtc;
void SetNext(uint8_t minutes, uint8_t seconds, bool reoccuring);
void Init();
private:
uint8_t AlarmMinutes;
uint8_t AlarmSeconds;
bool ReuccuringAlarm;
void InitializeAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t alarm);

};




#endif /* ALARM_HPP_ */
