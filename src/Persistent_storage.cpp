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
	return *(T *)_startAddress;
}

template <class T>
void EepromItem<T>::Write(T value) const{
	SerializedTemplate EEPROM_serial_container;
		EEPROM_serial_container.Deserialized=value;
		HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram();
		if(HAL_FLASHEx_DATAEEPROM_Unlock()!=HAL_OK){//Unprotect the EEPROM to allow writing
			ErrorFatal(__FILE__, __LINE__);
		}
		for (uint32_t Byte_index=0;Byte_index<size();Byte_index++){
			//Not very c++ way of iterating, but I'm getting dangerously close to low level here
			if(HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE,_startAddress+Byte_index,EEPROM_serial_container.Serialized[Byte_index])!=HAL_OK){//Unprotect the EEPROM to allow writing
						ErrorFatal(__FILE__, __LINE__);
					}
		}
		if(HAL_FLASHEx_DATAEEPROM_Lock()!=HAL_OK){// Reprotect the EEPROM
			ErrorFatal(__FILE__, __LINE__);
		}
}

PersistentStorage::PersistentStorage(){
}

 void PersistentStorage::writeCalibration(){


}


void PersistentStorage::readSetpoint(){

}
 void PersistentStorage::writeSetpoint(){


}
 template class EepromItem<uint8_t>;
 template class EepromItem<uint16_t>;
