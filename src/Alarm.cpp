/*
 * Alarm.cpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#include "Alarm.hpp"
#include "stm32l0xx.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_rtc.h"
RTC_HandleTypeDef Alarm::hrtc=RTC_HandleTypeDef();
void Alarm::Init(){
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_A);
	HAL_RTC_DeInit(&hrtc);
	  __HAL_RCC_RTC_ENABLE();
	  RTC_TimeTypeDef sTime;
	  RTC_DateTypeDef sDate;
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
	  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	  {
	   // _Error_Handler(__FILE__, __LINE__);
	  }
	  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	  sDate.Month = RTC_MONTH_JANUARY;
	  sDate.Date = 0x1;
	  sDate.Year = 0x0;

	  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	  {
	   // _Error_Handler(__FILE__, __LINE__);
	  }
	  HAL_NVIC_EnableIRQ(RTC_IRQn);


}
//Define the interrupt function here, because I want to include every aspect of the RTC in this source code

void Alarm::SetNext(uint8_t minutes, uint8_t seconds, bool reoccuring){
	AlarmMinutes=minutes;
	AlarmSeconds=seconds;
	ReuccuringAlarm=reoccuring;
InitializeAlarm(0,AlarmMinutes,AlarmSeconds,RTC_ALARM_A);
}


void Alarm::InitializeAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t alarm){
	HAL_RTC_DeactivateAlarm( &hrtc, RTC_ALARM_A );
	RTC_TimeTypeDef CurrentTime;
	HAL_RTC_GetTime(&hrtc,&CurrentTime,RTC_FORMAT_BIN);
	RTC_AlarmTypeDef sAlarm;

	//
	sAlarm.AlarmTime.Seconds=CurrentTime.Seconds+seconds;
	while(sAlarm.AlarmTime.Seconds>=60){
		sAlarm.AlarmTime.Seconds-=60;
		minutes++;
	}
	sAlarm.AlarmTime.Minutes=CurrentTime.Minutes+minutes;
	while(sAlarm.AlarmTime.Minutes>=60){
		sAlarm.AlarmTime.Minutes-=60;
		hours++;
	}
	sAlarm.AlarmTime.Hours=CurrentTime.Hours+hours;
	while(sAlarm.AlarmTime.Hours>=24){
		sAlarm.AlarmTime.Hours-=24;
	}

		  sAlarm.AlarmTime.SubSeconds = 0x0;
		  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_SET;
		  sAlarm.AlarmMask =RTC_ALARMMASK_HOURS |RTC_ALARMMASK_DATEWEEKDAY;
		  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
		  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
		  sAlarm.AlarmDateWeekDay = 0x1;
		  sAlarm.Alarm = RTC_ALARM_B;
		  HAL_RTC_GetTime(&Alarm::hrtc,&CurrentTime,RTC_FORMAT_BCD);
	if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
	  //_Error_Handler(__FILE__, __LINE__);
	}

}


void RTC_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&Alarm::hrtc);
}
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
int i=0;
i++;
}
void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc){
int i=0;
i++;
}
