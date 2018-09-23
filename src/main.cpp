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
void SystemClock_Config(void);
void SystemPower_Config(void);
void _Error_Handler(char *file, int line);
int main(void)
{
	HAL_Init();
SystemClock_Config();
SystemPower_Config();
//Buzzer buzzer;
//buzzer.init_timer();
//buzzer.setFrequency(16000);
//buzzer.start();
HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2);
HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN3);

__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

 /* Disable GPIOs clock */
 __HAL_RCC_GPIOA_CLK_DISABLE();
 __HAL_RCC_GPIOB_CLK_DISABLE();
 /* Enter Stop Mode */
 HAL_SuspendTick();
 HAL_RCC_DeInit();
 HAL_DeInit();
//HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
HAL_PWR_EnterSTANDBYMode();
	for(;;);
}
//Cleanup this code dude
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable MSI Oscillator */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue=0x00;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /* Disable Power Control clock */
  __HAL_RCC_PWR_CLK_DISABLE();

}

 void SystemPower_Config(void)
 {
   __HAL_RCC_PWR_CLK_ENABLE();
   HAL_PWREx_EnableUltraLowPower();
   HAL_PWREx_EnableLowPowerRunMode();
 }
