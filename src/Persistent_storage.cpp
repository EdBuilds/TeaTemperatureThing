/*
 * Persistent_storage.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: tamas
 */
#include "Persistent_storage.hpp"
#include "stm32l0xx_hal.h"

PersistentStorage::PersistentStorage(){

}
void PersistentStorage::readCalibration(){
	calibrationData CalibrationBuffer=*(calibrationData *)EEPROM_CALIBRATION_ADDRESS;
	CalibrationData=CalibrationBuffer;
}
 void PersistentStorage::writeCalibration(){
	serialCalibrationData EEPROM_serial_container;
	EEPROM_serial_container.Deserialized=CalibrationData;
	HAL_FLASHEx_DATAEEPROM_Unlock();  //Unprotect the EEPROM to allow writing
	for (uint8_t Byte_index=0;Byte_index<sizeof(calibrationData);Byte_index++){
		//Not very c++ way of iterating, but I'm getting dangerously close to low level here
		HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE,
				EEPROM_CALIBRATION_ADDRESS+Byte_index,
				EEPROM_serial_container.Serialized[Byte_index]);
	}
    HAL_FLASHEx_DATAEEPROM_Lock();  // Reprotect the EEPROM

}

bool PersistentStorage::hasCalibrationData(){
	calibrationData Calibration=*(calibrationData *)EEPROM_CALIBRATION_ADDRESS;
	if(Calibration.Header==EEPROM_CALIBRATION_HEADER){
		return true;
	}
	return false;
}

void PersistentStorage::readSetpoint(){
	setpointData SetpointBuffer=*(setpointData *)EEPROM_SETPOINT_ADDRESS;
	SetpointData=SetpointBuffer;
}
 void PersistentStorage::writeSetpoint(){
	serialSetpointData EEPROM_serial_container;
	EEPROM_serial_container.Deserialized=SetpointData;
	HAL_FLASHEx_DATAEEPROM_Unlock();  //Unprotect the EEPROM to allow writing
	for (uint8_t Byte_index=0;Byte_index<sizeof(calibrationData);Byte_index++){
		//Not very c++ way of iterating, but I'm getting dangerously close to low level here
		HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_BYTE,
				EEPROM_CALIBRATION_ADDRESS+Byte_index,
				EEPROM_serial_container.Serialized[Byte_index]);
	}
    HAL_FLASHEx_DATAEEPROM_Lock();  // Reprotect the EEPROM

}
bool PersistentStorage::hasSetpointData(){
	setpointData Setpoint=*(setpointData *)EEPROM_SETPOINT_ADDRESS;
	if(Setpoint.Header==EEPROM_SETPOINT_HEADER){
		return true;
	}
	return false;
}




