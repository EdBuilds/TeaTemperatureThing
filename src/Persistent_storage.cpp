/*
 * Persistent_storage.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: tamas
 */
#include "Persistent_storage.hpp"
#include "stm32l0xx_hal_flash.h"

PersistentStorage::PersistentStorage(){
	HAL_FLASHEx_DATAEEPROM_Unlock();  //Unprotect the EEPROM to allow writing
   // status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE, address, data);
    HAL_FLASHEx_DATAEEPROM_Lock();  // Reprotect the EEPROM
}



