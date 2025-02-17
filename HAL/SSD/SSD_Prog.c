/*
 * SSD_Prog.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Ali Mohamed
 */

#include <util/delay.h>
#include "SSD_Interface.h"
#include "SSD_Config.h"
#include "SSD_Private.h"

Std_ReturnType HAL_SSD_SSDInit(SSD_Module_t *Copy_SSD, MC_Control_t Copy_MC_ControlLevel)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;

	if(Copy_MC_ControlLevel == MC_Generate_NUM_AND_CONTROL_ON_OFF)
	{
		MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Common));
	}

	MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin0_A));
	MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin1_B));
	MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin2_C));
	MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin3_D));
	if((*Copy_SSD).Decoder_Type == SOFTWARE_DEC)
	{
		MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin4_E));
		MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin5_F));
		MCAL_DIO_SetPinDirection(&((*Copy_SSD).SSD_Pin6_G));
	}
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_SSD_SSDDisplay(SSD_Module_t *Copy_SSD)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;

	if((*Copy_SSD).Decoder_Type == SOFTWARE_DEC)
	{
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin0_A), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _0TH_BIT)));
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin1_B), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _1st_BIT)));
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin2_C), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _2nd_BIT)));
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin3_D), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _3rd_BIT)));
		MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin4_E), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _4TH_BIT)));
		MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin5_F), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _5TH_BIT)));
		MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin6_G), ((Copy_SSD->SSD_Type) ^ GET_BIT(Copy_SSD->ValueToBeDisplayed, _6TH_BIT)));
	}
    else if((*Copy_SSD).Decoder_Type == HEX_DEC)
    {
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin0_A), GET_BIT(Copy_SSD->ValueToBeDisplayed, _0TH_BIT));
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin1_B), GET_BIT(Copy_SSD->ValueToBeDisplayed, _1st_BIT));
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin2_C), GET_BIT(Copy_SSD->ValueToBeDisplayed, _2nd_BIT));
        MCAL_DIO_SetPinValue(&(Copy_SSD->SSD_Pin3_D), GET_BIT(Copy_SSD->ValueToBeDisplayed, _3rd_BIT));
    }
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_SSD_SSDDisplayNumWithSoftwareDecoder(SSD_Module_t *Copy_SSD)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_NumArray[16] = {SSD_0, SSD_1, SSD_2, SSD_3, SSD_4, SSD_5, SSD_6, SSD_7, SSD_8, SSD_9, SSD_10, SSD_11, SSD_12, SSD_13, SSD_14, SSD_15};

	(*Copy_SSD).ValueToBeDisplayed = Local_NumArray[(*Copy_SSD).ValueToBeDisplayed];
	HAL_SSD_SSDDisplay(Copy_SSD);

	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_SSD_SSDArrayDisplay(SSD_Module_t **Copy_SSD, uint8 Copy_NumOfSSD)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	for(; Copy_NumOfSSD > 0; Copy_NumOfSSD--)
	{
		MCAL_DIO_SetPinValue(&(Copy_SSD[Copy_NumOfSSD - 1]->SSD_Common), Copy_SSD[Copy_NumOfSSD - 1]->SSD_Type);
		if(Copy_SSD[Copy_NumOfSSD - 1]->Decoder_Type == SOFTWARE_DEC)
		{
			HAL_SSD_SSDDisplayNumWithSoftwareDecoder(Copy_SSD[Copy_NumOfSSD - 1]);
		}
		else if(Copy_SSD[Copy_NumOfSSD - 1]->Decoder_Type == HEX_DEC)
		{
			HAL_SSD_SSDDisplay(Copy_SSD[Copy_NumOfSSD - 1]);
		}
		_delay_ms(50);
		MCAL_DIO_SetPinValue(&(Copy_SSD[Copy_NumOfSSD - 1]->SSD_Common), !(Copy_SSD[Copy_NumOfSSD - 1]->SSD_Type));
	}
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}


