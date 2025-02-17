/*
 * POT_Prog.c
 *
 *  Created on: Nov 10, 2024
 *      Author: Ali Mohamed
 */

#include "POT_Interface.h"
#include "POT_Config.h"
#include "POT_Private.h"

Std_ReturnType HAL_POT_POTInit(POT_Module_t *Copy_POT)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	MCAL_ADC_ADCInitStatus(ADC_ENABLE);
	Pin_Conig_t Local_ADC_Channel_Info = {.PORT_ID = DIO_PORTA, .Pin_Direction = DIO_PIN_INPUT, .Pin_Num = Copy_POT->POT_ADC_Channel};
	MCAL_DIO_SetPinDirection(&Local_ADC_Channel_Info);
	MCAL_ADC_ADCChannelSelect(Copy_POT->POT_ADC_Channel);
	MCAL_ADC_ADCResultAdjust(ADC_RIGHT_ADJUST);
	MCAL_ADC_ADCReferenceSelect(Copy_POT->POT_VREF);
	MCAL_ADC_ADCTriggerMode(Copy_POT->POT_ADCTriggerSourceSelect);
	MCAL_ADC_ADCPrescalarSelect(Copy_POT->POT_ADCPrescalarSelect);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType HAL_POT_POTRead(POT_Module_t *Copy_POT, uint16 *Copy_POTReadValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	MCAL_ADC_ADCReadResult(Copy_POT->POT_ADC_Channel,Copy_POTReadValue);
	Copy_POT->POT_LastReadValue = *Copy_POTReadValue;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
