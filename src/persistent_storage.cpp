/*
 * Persistent_storage.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: tamas
 */
#include <error_handler.hpp>
#include <persistent_storage.hpp>
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
//#include "stm32l0xx_hal_flash.h"


template <class T>
uint32_t EepromItem<T>::global_address_=EEPROM_BASE_ADDRESS;

template <class T>
EepromItem<T>::EepromItem(): start_address_(global_address_){
	//allocating the memory with incrementing the global address variable
	global_address_+=Size();
}

/**
 * @brief A wrapper for the sizeof function
 * @return the size of the stored variable
 */
template <class T>
uint32_t EepromItem<T>::Size() const{
	return sizeof(T);
}

/**
 * @brief Reads the stored variable from the eeprom
 * @return the read variable
 */
template <class T>
T EepromItem<T>::Read() const{
	T return_value=*(T *)start_address_;
	return return_value;
}

/**
 * @brief Writes the function parameter to the eeprom
 * @param value the variable to write
 */
template <class T>
void EepromItem<T>::Write(const T &value) const{
	SerializedTemplate eeprom_serial_container;
	FLASH->SR=3;
		eeprom_serial_container.deserialized=value;
		if(HAL_FLASHEx_DATAEEPROM_Unlock()!=HAL_OK){//Unprotect the EEPROM to allow writing
			HAL_FLASHEx_DATAEEPROM_Lock();
			FatalError(__FILE__, __LINE__);
		}
		for (uint32_t byte_index=0;byte_index<Size();byte_index++){
			//Not very c++ way of iterating, but I'm getting dangerously close to low level here
			HAL_StatusTypeDef status=HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE,start_address_+byte_index,eeprom_serial_container.serialized[byte_index]);
					if(status!=HAL_OK){//Unprotect the EEPROM to allow writing
			HAL_FLASHEx_DATAEEPROM_Lock();
						FatalError(__FILE__, __LINE__);
					}
		}
		if(HAL_FLASHEx_DATAEEPROM_Lock()!=HAL_OK){// Reprotect the EEPROM
			FatalError(__FILE__, __LINE__);

		}
}

 template class EepromItem<uint8_t>;
 template class EepromItem<uint16_t>;
