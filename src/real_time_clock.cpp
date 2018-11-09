/*
 * Alarm.cpp
 *
 *  Created on: Sep 24, 2018
 *      Author: tamas
 */

#include <error_handler.hpp>
#include <real_time_clock.hpp>
#include "inc/stm32l0xx_it.h"
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
//#include "stm32l0xx_hal_rtc.h"
#include "inc/display_driver.hpp"
RTC_HandleTypeDef RealTimeClock::hrtc_=RTC_HandleTypeDef();
Alarm RealTimeClock::alarm_a_;
Alarm RealTimeClock::alarm_b_;
void RealTimeClock::Init(SignalCallback alarm_callback){
	FLASH->SR;
	RTC_AlarmTypeDef s_alarm;
	__HAL_RCC_RTC_ENABLE();
	  s_alarm.AlarmTime.SubSeconds = 0x0;
	  s_alarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  s_alarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_SET;
	  s_alarm.AlarmMask =RTC_ALARMMASK_HOURS |RTC_ALARMMASK_DATEWEEKDAY;
	  s_alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_SS14_7;
	  s_alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	  s_alarm.AlarmDateWeekDay = 0x1;
	  s_alarm.Alarm = RTC_ALARM_B;
	  alarm_b_=Alarm(s_alarm,alarm_callback);
	  s_alarm.Alarm = RTC_ALARM_A;
	  alarm_a_=Alarm(s_alarm,alarm_callback);


	  RTC_TimeTypeDef s_time;
	  RTC_DateTypeDef s_date;
	  hrtc_=RTC_HandleTypeDef();
	  hrtc_.Instance = RTC;
	  hrtc_.Init.HourFormat = RTC_HOURFORMAT_24;
	  hrtc_.Init.AsynchPrediv = 127;
	  hrtc_.Init.SynchPrediv = 255;
	  hrtc_.Init.OutPut = RTC_OUTPUT_DISABLE;
	  hrtc_.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	  hrtc_.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	  hrtc_.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	  if (HAL_RTC_Init(&hrtc_) != HAL_OK)
	  {
	    	FatalError(__FILE__, __LINE__);
	  }

	  s_time.Hours = 0x0;
	  s_time.Minutes = 0x0;
	  s_time.Seconds = 0x0;
	  s_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	  s_time.StoreOperation = RTC_STOREOPERATION_RESET;
	  if (HAL_RTC_SetTime(&hrtc_, &s_time, RTC_FORMAT_BIN) != HAL_OK)
	  {
	    	FatalError(__FILE__, __LINE__);
	  }
	  s_date.WeekDay = RTC_WEEKDAY_MONDAY;
	  s_date.Month = RTC_MONTH_JANUARY;
	  s_date.Date = 0x1;
	  s_date.Year = 0x0;

	  if (HAL_RTC_SetDate(&hrtc_, &s_date, RTC_FORMAT_BIN) != HAL_OK)
	  {
	    	FatalError(__FILE__, __LINE__);
	  }
	  HAL_NVIC_EnableIRQ(RTC_IRQn);
		HAL_RTC_DeactivateAlarm(&hrtc_,RTC_ALARM_A);
		HAL_RTC_DeactivateAlarm(&hrtc_,RTC_ALARM_B);

}
//Define the interrupt function here, because I want to include every aspect of the RTC in this source code

void Alarm::Set(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t sub_seconds){
	RTC_TimeTypeDef current_time;
	RTC_DateTypeDef s_date;
	HAL_RTC_GetTime(&RealTimeClock::hrtc_,&current_time,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&RealTimeClock::hrtc_,&s_date,RTC_FORMAT_BIN);
	rtc_alarm_.AlarmTime.SubSeconds=current_time.SubSeconds-sub_seconds;
	if(current_time.SubSeconds>sub_seconds){
		rtc_alarm_.AlarmTime.SubSeconds=current_time.SubSeconds-sub_seconds;
	}else{
		rtc_alarm_.AlarmTime.SubSeconds=255-(sub_seconds-current_time.SubSeconds);
		++seconds;
	}
	rtc_alarm_.AlarmTime.Seconds=current_time.Seconds+seconds;
	while(rtc_alarm_.AlarmTime.Seconds>=60){
		rtc_alarm_.AlarmTime.Seconds-=60;
		minutes++;
	}
	rtc_alarm_.AlarmTime.Minutes=current_time.Minutes+minutes;
	while(rtc_alarm_.AlarmTime.Minutes>=60){
		rtc_alarm_.AlarmTime.Minutes-=60;
		hours++;
	}
	rtc_alarm_.AlarmTime.Hours=current_time.Hours+hours;
	while(rtc_alarm_.AlarmTime.Hours>=24){
		rtc_alarm_.AlarmTime.Hours-=24;
	}
	if (HAL_RTC_SetAlarm_IT(&RealTimeClock::hrtc_, &rtc_alarm_, RTC_FORMAT_BIN) != HAL_OK)
	{
	    	FatalError(__FILE__, __LINE__);
	}
}
void Alarm::Deactivate(){
	HAL_RTC_DeactivateAlarm(&RealTimeClock::hrtc_,rtc_alarm_.Alarm);
}

void RTC_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&RealTimeClock::hrtc_);

}
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	RealTimeClock::alarm_a_.alarm_callback_(SIG_ALARM_A);
}
void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc){
	RealTimeClock::alarm_b_.alarm_callback_(SIG_ALARM_B);
}
