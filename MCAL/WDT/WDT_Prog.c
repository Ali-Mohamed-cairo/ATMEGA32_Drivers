/*
 * WDT_Prog.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Ali Mohamed
 */


#include "WDT_Private.h"
#include "WDT_Config.h"
#include "WDT_Interface.h"

Std_ReturnType MCAL_WDT_WDTStatus(uint8 Copy_WDTStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_WDTStatus == WDT_ENABLE)
	{
		WDTCR_REG.WDE_Bit3 = SET;
	}
	else if(Copy_WDTStatus == WDT_DISABLE)
	{
		SET_N_BITS(WDTCR_REG.WDTCR_Register, 0b0001100);
		WDTCR_REG.WDE_Bit3 = CLEAR;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_WDT_TimeOutSelect(uint8 Copy_TimeOut)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	WDTCR_REG.WDP_BITs = Copy_TimeOut;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
