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

 SignalCallback Button::button_callback_;

 /**
  * @brief initializes the buttons' hardware layer
  * @param button_callback callback function to the state machine
  */
void Button::Init(SignalCallback button_callback){
	button_callback_=button_callback;
	  /* GPIO Ports Clock Enable */

	  GPIO_InitTypeDef gpio_init_struct;
	  gpio_init_struct.Pin = BUTTON_1_PIN;
	  gpio_init_struct.Mode = GPIO_MODE_IT_RISING_FALLING;
	  gpio_init_struct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(BUTTON_1_PORT, &gpio_init_struct);

	  HAL_NVIC_SetPriority(BUTTON_1_ITn, 0, 0);
	  HAL_NVIC_EnableIRQ(BUTTON_1_ITn);

	  gpio_init_struct.Pin = BUTTON_2_PIN;
	  gpio_init_struct.Mode = GPIO_MODE_IT_RISING_FALLING;
	  gpio_init_struct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(BUTTON_2_PORT, &gpio_init_struct);

	  HAL_NVIC_SetPriority(BUTTON_2_ITn, 0, 0);
	  HAL_NVIC_EnableIRQ(BUTTON_2_ITn);

}

/**
 * @brief disables the interrupt of the button
 * @param interrupt_routine interrupt routine to stop
 */
void Button::Disable(IRQn_Type interrupt_routine){
	HAL_NVIC_DisableIRQ(interrupt_routine);
}

/**
 * @brief enable the interrupt of the button
 * @param interrupt_routine interrupt routine to start
 */
void Button::Enable(IRQn_Type interrupt_routine){
	HAL_NVIC_SetPriority(interrupt_routine, 0, 0);
	HAL_NVIC_EnableIRQ(interrupt_routine);
}

/**
 * @brief reads the state of the selected button
 * @param button which button to read
 * @return the state of the button
 */
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

/**
 * @brief Button 1 interrupt handler
 */
void EXTI0_1_IRQHandler(void)
{
Button::Disable(BUTTON_1_ITn);
	HAL_GPIO_EXTI_IRQHandler(BUTTON_1_PIN);

	if(HAL_GPIO_ReadPin(BUTTON_1_PORT,BUTTON_1_PIN)==GPIO_PIN_SET){
		Button::button_callback_(SIG_BUTTON_1_DN);
	}else{
		Button::button_callback_(SIG_BUTTON_1_UP);
	}
}

/**
 * @brief Button 2 interrupt handler
 */
void EXTI2_3_IRQHandler(void)
{
Button::Disable(BUTTON_2_ITn);
    HAL_GPIO_EXTI_IRQHandler(BUTTON_2_PIN);
	if(HAL_GPIO_ReadPin(BUTTON_2_PORT,BUTTON_2_PIN)==GPIO_PIN_SET){
		Button::button_callback_(SIG_BUTTON_2_DN);
	}else{
		Button::button_callback_(SIG_BUTTON_2_UP);
	}

}
