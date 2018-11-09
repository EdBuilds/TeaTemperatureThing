/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <button_driver.hpp>
#include <buzzer_driver.hpp>
#include <real_time_clock.hpp>
#include <state_machine.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <thermometer_driver.hpp>
#include "inc/display_driver.hpp"
#include "etl/include/etl/queue.h"

void SystemClockConfig(void);
void SystemPowerConfig(void);
RealTimeClock alarm;
int main(void)
{

HAL_Init();
SystemClockConfig();
SystemPowerConfig();
StateMachine machine;
 uint8_t temp=__HAL_PWR_GET_FLAG(PWR_FLAG_WU);
machine.Init(bool(temp));

	for(;;){
machine.Update();
	}
}

//Cleanup this code dude
void SystemClockConfig(void)
{

	  RCC_OscInitTypeDef rcc_osc_init_struct;
	  RCC_ClkInitTypeDef rcc_clk_init_struct;
	  RCC_PeriphCLKInitTypeDef periph_clk_init;

	    /**Configure the main internal regulator output voltage
	    */
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  rcc_osc_init_struct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
	  rcc_osc_init_struct.HSIState = RCC_HSI_ON;
	  rcc_osc_init_struct.HSICalibrationValue = 16;
	  rcc_osc_init_struct.LSIState = RCC_LSI_ON;
	  rcc_osc_init_struct.PLL.PLLState = RCC_PLL_ON;
	  rcc_osc_init_struct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	  rcc_osc_init_struct.PLL.PLLMUL = RCC_PLLMUL_4;
	  rcc_osc_init_struct.PLL.PLLDIV = RCC_PLLDIV_4;
	  if (HAL_RCC_OscConfig(&rcc_osc_init_struct) != HAL_OK)
	  {
	   // _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  rcc_clk_init_struct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  rcc_clk_init_struct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  rcc_clk_init_struct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  rcc_clk_init_struct.APB1CLKDivider = RCC_HCLK_DIV1;
	  rcc_clk_init_struct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&rcc_clk_init_struct, FLASH_LATENCY_0) != HAL_OK)
	  {
	    //_Error_Handler(__FILE__, __LINE__);
	  }

	  periph_clk_init.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	  periph_clk_init.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	  if (HAL_RCCEx_PeriphCLKConfig(&periph_clk_init) != HAL_OK)
	  {
	    //_Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure the Systick interrupt time
	    */
	  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	    /**Configure the Systick
	    */
	  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	  /* SysTick_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);


}

 void SystemPowerConfig(void)
 {
   __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __GPIOA_CLK_ENABLE();
	  __GPIOB_CLK_ENABLE();
   //HAL_PWREx_EnableUltraLowPower();
   //HAL_PWREx_EnableLowPowerRunMode();
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN3);

 }
