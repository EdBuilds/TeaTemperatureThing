/*
 * ADC_driver.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: tamas
 */

#include <Thermometer_driver.hpp>
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_hal_tim.h"
#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_hal_adc.h"
#include "stm32l0xx_nucleo_32.h"
Thermometer::Thermometer(){
	GPIO_InitTypeDef gpioInit;

	    __GPIOC_CLK_ENABLE();
	    __HAL_RCC_ADC1_CLK_ENABLE();

	    gpioInit.Pin = GPIO_PIN_1;
	    gpioInit.Mode = GPIO_MODE_ANALOG;
	    gpioInit.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOC, &gpioInit);

	    HAL_NVIC_SetPriority(ADC1_COMP_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(ADC1_COMP_IRQn);
ADC_HandleTypeDef g_AdcHandle;

	    ADC_ChannelConfTypeDef adcChannel;

	    g_AdcHandle.Instance = ADC1;

	    g_AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	    g_AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
	    g_AdcHandle.Init.ScanConvMode = DISABLE;
	    g_AdcHandle.Init.ContinuousConvMode = ENABLE;
	    g_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	    g_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	    g_AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	    g_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	    g_AdcHandle.Init.DMAContinuousRequests = ENABLE;
	    g_AdcHandle.Init.EOCSelection = DISABLE;

	    HAL_ADC_Init(&g_AdcHandle);

	    adcChannel.Channel = ADC_CHANNEL_11;
	    adcChannel.Rank = 1;

	    if (HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel) != HAL_OK)
	    {
	        asm("bkpt 255");
	    }
	}

