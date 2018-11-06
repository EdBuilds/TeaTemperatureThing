/*
 * Buzzer_driver.hpp
 *
 *  Created on: Aug 9, 2018
 *      Author: tamas
 */

#ifndef INC_BUZZER_DRIVER_HPP_
#define INC_BUZZER_DRIVER_HPP_
#include "inc/pinout_definitions.hpp"
#include "HAL_Driver/Inc/stm32l0xx_hal.h"

class Buzzer {
	public:
	TIM_HandleTypeDef htim2;
	TIM_OC_InitTypeDef sConfigOC;
	bool isRunning;
	void Init();
	void start();
	void setFrequency(uint16_t setFreq);
	void stop();
};

#endif  // INC_BUZZER_DRIVER_HPP_
