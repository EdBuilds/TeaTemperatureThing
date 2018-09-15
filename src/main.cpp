/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32l0xx.h"
#include "stm32l0xx_nucleo_32.h"
#include "display_driver.hpp"
#include "Buzzer_driver.hpp"
#include "Thermometer_driver.hpp"
void SystemClock_Config(void);
void _Error_Handler(char *file, int line);
int main(void)
{
HAL_Init();
SystemClock_Config();
Buzzer buzzer;
buzzer.init_timer();
buzzer.setFrequency(16000);
buzzer.start();
Thermometer thermometer;
uint16_t result;
	for(;;){
	result=thermometer.measure();
	buzzer.setFrequency(result);
	}
}
//Cleanup this code dude
 void SystemClock_Config(void)
 {

   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;

     /**Configure the main internal regulator output voltage
     */
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

     /**Initializes the CPU, AHB and APB busses clocks
     */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSIState = RCC_HSI_ON;
   RCC_OscInitStruct.HSICalibrationValue = 16;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
   RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_4;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
   //  _Error_Handler(__FILE__, __LINE__);
   }

     /*Initializes the CPU, AHB and APB busses clocks*/
   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
   {
//     _Error_Handler(__FILE__, __LINE__);
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
