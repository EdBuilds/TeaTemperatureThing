/*
 * Alarm.hpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#ifndef ALARM_HPP_
#define ALARM_HPP_
#include "stm32l0xx_hal.h"
void RTC_IRQHandler(void);
class Alarm{
public:
 RTC_HandleTypeDef hrtc;
void Init();

};



#endif /* ALARM_HPP_ */
