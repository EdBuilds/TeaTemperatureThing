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
	TIM_HandleTypeDef htim_2_;
	TIM_OC_InitTypeDef config_oc_;
	bool is_running_;
	void Init();
	void Start();
	void SetFrequency(uint16_t set_freq);
	void Stop();
};

#endif  // INC_BUZZER_DRIVER_HPP_
