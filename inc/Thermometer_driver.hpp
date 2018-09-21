/*
 * ADC_driver.hpp
 *
 *  Created on: Aug 10, 2018
 *      Author: tamas
 */

#ifndef THERMOMETER_DRIVER_HPP_
#define THERMOMETER_DRIVER_HPP_
#include "stm32l0xx_hal.h"
#include "GPIO_wrapper.hpp"
#include "pinout_definitions.hpp"
class Thermometer{
	OutputPin  ReferenceEnable;
	 ADC_HandleTypeDef AdcHandle;
	 ADC_ChannelConfTypeDef AdcChannel;
public:
	 uint16_t measure();
	 Thermometer();
};



#endif /* THERMOMETER_DRIVER_HPP_ */
