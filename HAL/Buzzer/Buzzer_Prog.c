/*
 * Buzzer_Prog.c
 *
 *  Created on: Nov 14, 2024
 *      Author: Ali Mohamed
 */

#include "Buzzer_Interface.h"
#include "Buzzer_Config.h"
#include "Buzzer_Private.h"

Std_ReturnType HAL_Buzzer_BuzzerInit(Buzzer_Module_t *Copy_Buzzer)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Pin_Conig_t Buzzer_Pin= {
			.PORT_ID = Copy_Buzzer->PORT_ID,
			.Pin_Num = Copy_Buzzer->Pin_Num,
			.Pin_Direction = DIO_PIN_OUTPUT
	};
	MCAL_DIO_SetPinDirection(&Buzzer_Pin);
	return Local_ErrorStatus;
}
Std_ReturnType HAL_Buzzer_BuzzerOn(Buzzer_Module_t *Copy_Buzzer)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Pin_Conig_t Buzzer_Pin= {
			.PORT_ID = Copy_Buzzer->PORT_ID,
			.Pin_Num = Copy_Buzzer->Pin_Num,
			.Pin_Direction = DIO_PIN_OUTPUT
	};
	MCAL_DIO_SetPinValue(&Buzzer_Pin, DIO_HIGH);
	return Local_ErrorStatus;
}
Std_ReturnType HAL_Buzzer_BuzzerOff(Buzzer_Module_t *Copy_Buzzer)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Pin_Conig_t Buzzer_Pin= {
			.PORT_ID = Copy_Buzzer->PORT_ID,
			.Pin_Num = Copy_Buzzer->Pin_Num,
			.Pin_Direction = DIO_PIN_OUTPUT
	};
	MCAL_DIO_SetPinValue(&Buzzer_Pin, DIO_LOW);
	return Local_ErrorStatus;
}
