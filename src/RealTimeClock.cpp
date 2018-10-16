/*
 * Alarm.cpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#include <RealTimeClock.hpp>
#include "ErrorHandler.hpp"
#include "stm32l0xx.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_rtc.h"
#include "display_driver.hpp"
RTC_HandleTypeDef RealTimeClock::hrtc=RTC_HandleTypeDef();
Alarm RealTimeClock::AlarmA;
Alarm RealTimeClock::AlarmB;
void RealTimeClock::Init(SignalCallback AlarmCallback){
	RTC_AlarmTypeDef sAlarm;
	  sAlarm.AlarmTime.SubSeconds = 0x0;
	  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_SET;
	  sAlarm.AlarmMask =RTC_ALARMMASK_HOURS |RTC_ALARMMASK_DATEWEEKDAY;
	  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_7;
	  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	  sAlarm.AlarmDateWeekDay = 0x1;
	  sAlarm.Alarm = RTC_ALARM_B;
	  AlarmB=Alarm(sAlarm,AlarmCallback);
	  sAlarm.Alarm = RTC_ALARM_A;
	  AlarmA=Alarm(sAlarm,AlarmCallback);
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_A);
	HAL_RTC_DeactivateAlarm(&hrtc,RTC_ALARM_B);
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
	    	ErrorFatal(__FILE__, __LINE__);
	  }

	  sTime.Hours = 0x0;
	  sTime.Minutes = 0x0;
	  sTime.Seconds = 0x0;
	  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	  {
	    	ErrorFatal(__FILE__, __LINE__);
	  }
	  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	  sDate.Month = RTC_MONTH_JANUARY;
	  sDate.Date = 0x1;
	  sDate.Year = 0x0;

	  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	  {
	    	ErrorFatal(__FILE__, __LINE__);
	  }
	  HAL_NVIC_EnableIRQ(RTC_IRQn);


}
//Define the interrupt function here, because I want to include every aspect of the RTC in this source code

void Alarm::set(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t subSeconds){
	RTC_TimeTypeDef CurrentTime;
	RTC_DateTypeDef sDate;
	HAL_RTC_GetTime(&RealTimeClock::hrtc,&CurrentTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&RealTimeClock::hrtc,&sDate,RTC_FORMAT_BIN);
	sAlarm.AlarmTime.SubSeconds=CurrentTime.SubSeconds-subSeconds;
	if(CurrentTime.SubSeconds>subSeconds){
		sAlarm.AlarmTime.SubSeconds=CurrentTime.SubSeconds-subSeconds;
	}else{
		sAlarm.AlarmTime.SubSeconds=255-(subSeconds-CurrentTime.SubSeconds);
		++seconds;
	}
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
	if (HAL_RTC_SetAlarm_IT(&RealTimeClock::hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
	{
	    	ErrorFatal(__FILE__, __LINE__);
	}
}
void Alarm::deactivate(){
	HAL_RTC_DeactivateAlarm(&RealTimeClock::hrtc,sAlarm.Alarm);
}

void RTC_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&RealTimeClock::hrtc);

}
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	RealTimeClock::AlarmA.AlarmCallback(SIG_ALARM_A);
}
void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc){
	RealTimeClock::AlarmB.AlarmCallback(SIG_ALARM_B);
}
