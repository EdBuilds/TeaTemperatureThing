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
			

int main(void)
{
	OutputPin pin1(GPIO_PIN_9,GPIOA);
	pin1.reset();
	for(;;);
}
