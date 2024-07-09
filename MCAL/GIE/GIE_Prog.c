/*
 * GIE_Prog.c
 *
 *  Created on: Jul 8, 2024
 *      Author: Ali Mohamed
 */

#include "GIE_Interface.h"

Std_ReturnType MCAL_GlobalINTStatus(uint8 Copy_GIStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	switch(Copy_GIStatus)
	{
	case GI_DISABLE:
		CLEAR_BIT(SREG_REG, GIE_I_BIT7);
		Local_ErrorStatus = E_OK;
		break;
	case GI_ENABLE:
		SET_BIT(SREG_REG, GIE_I_BIT7);
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}
