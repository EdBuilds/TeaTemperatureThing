/*
 * Button_driver.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: tamas
 */
#include <button_driver.hpp>
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"
#include "pinout_definitions.hpp"
 SignalCallback Button::ButtonCallback;
void Button::Init(SignalCallback buttonCallback){
	ButtonCallback=buttonCallback;
	  /* GPIO Ports Clock Enable */

	  GPIO_InitTypeDef GPIO_InitStruct;
	  GPIO_InitStruct.Pin = BUTTON_1_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(BUTTON_1_PORT, &GPIO_InitStruct);

	  HAL_NVIC_SetPriority(BUTTON_1_ITn, 0, 0);
	  HAL_NVIC_EnableIRQ(BUTTON_1_ITn);

	  GPIO_InitStruct.Pin = BUTTON_2_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(BUTTON_2_PORT, &GPIO_InitStruct);

	  HAL_NVIC_SetPriority(BUTTON_2_ITn, 0, 0);
	  HAL_NVIC_EnableIRQ(BUTTON_2_ITn);

}

void Button::Disable(IRQn_Type InterruptRoutine){
	HAL_NVIC_DisableIRQ(InterruptRoutine);
}
void Button::Enable(IRQn_Type InterruptRoutine){
	HAL_NVIC_SetPriority(InterruptRoutine, 0, 0);
	HAL_NVIC_EnableIRQ(InterruptRoutine);
}
GPIO_PinState Button::Read(ButtonID button){
	switch(button){
	case BUTTON_1:
		return HAL_GPIO_ReadPin(BUTTON_1_PORT,BUTTON_1_PIN);
		break;
	case BUTTON_2:
		return HAL_GPIO_ReadPin(BUTTON_2_PORT,BUTTON_2_PIN);
		break;
	default:
		return GPIO_PIN_RESET;
	}
}
void EXTI0_1_IRQHandler(void)
{
Button::Disable(BUTTON_1_ITn);
	HAL_GPIO_EXTI_IRQHandler(BUTTON_1_PIN);

	if(HAL_GPIO_ReadPin(BUTTON_1_PORT,BUTTON_1_PIN)==GPIO_PIN_SET){
		Button::ButtonCallback(SIG_BUTTON_1_DN);
	}else{
		Button::ButtonCallback(SIG_BUTTON_1_UP);
	}
}


void EXTI2_3_IRQHandler(void)
{
Button::Disable(BUTTON_2_ITn);
    HAL_GPIO_EXTI_IRQHandler(BUTTON_2_PIN);
	if(HAL_GPIO_ReadPin(BUTTON_2_PORT,BUTTON_2_PIN)==GPIO_PIN_SET){
		Button::ButtonCallback(SIG_BUTTON_2_DN);
	}else{
		Button::ButtonCallback(SIG_BUTTON_2_UP);
	}

}
