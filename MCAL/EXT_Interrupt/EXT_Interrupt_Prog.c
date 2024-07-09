/*
 * File:   EXT_Interrupt_Prog.h
 * Author: Ali Mohamed
 *
 * Created on March 6, 2024, 12:48 PM
 */

#include "EXT_Interrupt_Interface.h"
#include "EXT_Interrupt_Config.h"
#include "EXT_Interrupt_Private.h"

void (*EXT_Interrupt_EXTINT0_CallBack)(void) = NULL_PTR;
void (*EXT_Interrupt_EXTINT1_CallBack)(void) = NULL_PTR;
void (*EXT_Interrupt_EXTINT2_CallBack)(void) = NULL_PTR;


/*Disable or Enable EXT INT and Set the configured triggering event(IOC, Falling, ....etc)*/
Std_ReturnType MCAL_EXT_Interrupt_EXTIntStatus(const EXTINT_Config_t Copy_EXTInt, const uint8 Copy_EXTIntStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_EXTIntStatus == INT_DISABLE)
    {
		CLEAR_BIT(GICR_REG, Copy_EXTInt.INTNum);
		Local_ErrorStatus = E_OK;
    }
	else if(Copy_EXTIntStatus == INT_ENABLE)
	{
		switch(Copy_EXTInt.INTNum)
	    {
	    case EXTINT0:
	    	SET_BIT(GICR_REG, EXTINT0);
	    	MCUCR_REG.ISC0_BITs = Copy_EXTInt.TriggerEvent;
	    	MCAL_EXT_Interrupt_ClearEXTIntFlag(Copy_EXTInt);
            Local_ErrorStatus = E_OK;
	    	break;
	    case EXTINT1:
	    	SET_BIT(GICR_REG, EXTINT1);
	    	MCUCR_REG.ISC1_BITs = Copy_EXTInt.TriggerEvent;
	    	MCAL_EXT_Interrupt_ClearEXTIntFlag(Copy_EXTInt);
	    	Local_ErrorStatus = E_OK;
	    	break;
	    case EXTINT2:
	    	SET_BIT(GICR_REG, EXTINT2);
	    	if((Copy_EXTInt.TriggerEvent != LOW_LEVEL) || (Copy_EXTInt.TriggerEvent != IOC))
	    	{
	    		MCUCSR_REG.ISC2_BIT6 = ((Copy_EXTInt.TriggerEvent) & 1);
	    		MCAL_EXT_Interrupt_ClearEXTIntFlag(Copy_EXTInt);
	    	    Local_ErrorStatus = E_OK;
	    	}
	    	else
	    	{
	    		Local_ErrorStatus = E_NOT_OK;
	    	}
	    	break;
	    default:
	    	Local_ErrorStatus = E_NOT_OK;
	}
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_EXT_Interrupt_ReadEXTIntFlag(const EXTINT_Config_t Copy_EXTInt, uint8 *Copy_FlagValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_FlagValue = GET_BIT(GIFR_REG, Copy_EXTInt.INTNum);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_EXT_Interrupt_ClearEXTIntFlag(const EXTINT_Config_t Copy_EXTInt)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	SET_BIT(GIFR_REG, Copy_EXTInt.INTNum);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
/*SetCallBack APIs for EXTINTx */
Std_ReturnType MCAL_EXT_Interrupt_SetEXTINT0CallBack(void (*Copy_CallBackPtr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	EXT_Interrupt_EXTINT0_CallBack = Copy_CallBackPtr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_EXT_Interrupt_SetEXTINT1CallBack(void (*Copy_CallBackPtr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	EXT_Interrupt_EXTINT1_CallBack = Copy_CallBackPtr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_EXT_Interrupt_SetEXTINT2CallBack(void (*Copy_CallBackPtr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	EXT_Interrupt_EXTINT2_CallBack = Copy_CallBackPtr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
