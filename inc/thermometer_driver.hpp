/*
 * ADC_driver.hpp
 *
 *  Created on: Aug 10, 2018
 *      Author: tamas
 */

#ifndef INC_THERMOMETER_DRIVER_HPP_
#define INC_THERMOMETER_DRIVER_HPP_
#include <inc/gpio_wrapper.hpp>
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
#include "inc/pinout_definitions.hpp"
class Thermometer {
	OutputPin ReferenceEnable;
	ADC_HandleTypeDef AdcHandle;
	ADC_ChannelConfTypeDef AdcChannel;

	public:
	uint16_t measure();
	Thermometer();
};

#endif  // INC_THERMOMETER_DRIVER_HPP_
