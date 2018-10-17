/*
 * Persistent_storage.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: tamas
 */
#include "Persistent_storage.hpp"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_flash.h"
#include "ErrorHandler.hpp"


template <class T>
uint32_t EepromItem<T>::_globalAddress=EEPROM_BASE_ADDRESS;
template <class T>
EepromItem<T>::EepromItem(): _startAddress(_globalAddress){
_globalAddress+=size();
}

template <class T>
uint32_t EepromItem<T>::size() const{
	return sizeof(T);
}
template <class T>
T EepromItem<T>::Read() const{
	T returnvalue=*(T *)_startAddress;
	return returnvalue;
}

template <class T>
void EepromItem<T>::Write(const T &value) const{
	SerializedTemplate EEPROM_serial_container;
	FLASH->SR=3;
		EEPROM_serial_container.Deserialized=value;
		if(HAL_FLASHEx_DATAEEPROM_Unlock()!=HAL_OK){//Unprotect the EEPROM to allow writing
			HAL_FLASHEx_DATAEEPROM_Lock();
			ErrorFatal(__FILE__, __LINE__);
		}
		for (uint32_t Byte_index=0;Byte_index<size();Byte_index++){
			//Not very c++ way of iterating, but I'm getting dangerously close to low level here
			HAL_StatusTypeDef status=HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE,_startAddress+Byte_index,EEPROM_serial_container.Serialized[Byte_index]);
					if(status!=HAL_OK){//Unprotect the EEPROM to allow writing
			HAL_FLASHEx_DATAEEPROM_Lock();
						ErrorFatal(__FILE__, __LINE__);
					}
		}
		if(HAL_FLASHEx_DATAEEPROM_Lock()!=HAL_OK){// Reprotect the EEPROM
			ErrorFatal(__FILE__, __LINE__);

		}
}


 template class EepromItem<uint8_t>;
 template class EepromItem<uint16_t>;
