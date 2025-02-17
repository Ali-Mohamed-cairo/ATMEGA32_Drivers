/*
 * POT_Interface.h
 *
 *  Created on: Nov 10, 2024
 *      Author: Ali Mohamed
 */

#ifndef HAL_POT_POT_INTERFACE_H_
#define HAL_POT_POT_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

typedef struct{
	//The allowed channels are the single-ended channels only
	ADC_Input_Channel_t POT_ADC_Channel;
	VREF_t POT_VREF;
	ADC_Trigger_Source_t POT_ADCTriggerSourceSelect;
	ADC_Prescalar_t POT_ADCPrescalarSelect;
	//By default the ADC value read due to the POT is ADC_RIGHT_ADJUST
	uint16 POT_LastReadValue;
}POT_Module_t;

Std_ReturnType HAL_POT_POTInit(POT_Module_t *Copy_POT);
Std_ReturnType HAL_POT_POTRead(POT_Module_t *Copy_POT, uint16 *Copy_POTReadValue);

#endif /* HAL_POT_POT_INTERFACE_H_ */
