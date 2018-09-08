/*
 * Buzzer_driver.hpp
 *
 *  Created on: Aug 9, 2018
 *      Author: tamas
 */
//this is actually a bad naming for the file. I wanted to be consistent with the display, for nothing
#ifndef BUZZER_DRIVER_HPP_
#define BUZZER_DRIVER_HPP_

#include "stm32l0xx_hal.h"
#define BUZZER_TIMER_CHANNEL TIM_CHANNEL_1
#define BUZZER_TIMER TIM2
#define BUZZER_GPIO_PORT GPIOA
#define BUZZER_GPIO_PIN GPIO_PIN_0


class Buzzer{

public:
TIM_HandleTypeDef htim2;
TIM_OC_InitTypeDef sConfigOC;
bool isRunning;
void init_timer();
void start();
void setFrequency(uint16_t setFreq);
void stop();
};


#endif /* BUZZER_DRIVER_HPP_ */
