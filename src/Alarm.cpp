/*
 * Alarm.cpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#include "Alarm.hpp"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_rtc.h"
void Alarm::Init(){
	  HAL_NVIC_EnableIRQ(RTC_IRQn);

    __HAL_RCC_RTC_ENABLE();
	  RTC_TimeTypeDef sTime;
	  RTC_DateTypeDef sDate;
	  RTC_AlarmTypeDef sAlarm;
	  hrtc=RTC_HandleTypeDef();
	  hrtc.Instance = RTC;
	  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	  hrtc.Init.AsynchPrediv = 127;
	  hrtc.Init.SynchPrediv = 255;
	  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	  if (HAL_RTC_Init(&hrtc) != HAL_OK)
	  {
	  //  _Error_Handler(__FILE__, __LINE__);
	  }

	  sTime.Hours = 0x0;
	  sTime.Minutes = 0x0;
	  sTime.Seconds = 0x0;
	  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	  {
	   // _Error_Handler(__FILE__, __LINE__);
	  }
	  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	  sDate.Month = RTC_MONTH_JANUARY;
	  sDate.Date = 0x1;
	  sDate.Year = 0x0;

	  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	  {
	   // _Error_Handler(__FILE__, __LINE__);
	  }

	  sAlarm.AlarmTime.Hours = 0x0;
	  sAlarm.AlarmTime.Minutes = 0x00;
	  sAlarm.AlarmTime.Seconds = 0x10;
	  sAlarm.AlarmTime.SubSeconds = 0x0;
	  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_SET;
	  sAlarm.AlarmMask =RTC_ALARMMASK_ALL;// RTC_ALARMMASK_HOURS|RTC_ALARMMASK_MINUTES|RTC_ALARMMASK_DATEWEEKDAY;
	  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
	  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	  sAlarm.AlarmDateWeekDay = 0x1;
	  sAlarm.Alarm = RTC_ALARM_A;
	  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
	  	  {
	  	    //_Error_Handler(__FILE__, __LINE__);
	  	  }
	  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
	  {
	    //_Error_Handler(__FILE__, __LINE__);
	  }
//	  if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 0xFFF, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
//	  {
//	   // _Error_Handler(__FILE__, __LINE__);
//	  }

}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
int i=0;
i++;
}
