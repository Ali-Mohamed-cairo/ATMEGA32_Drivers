/*
 * ADC_Prog.c
 *
 *  Created on: Jul 14, 2024
 *      Author: Ali Mohamed
 */

#include <avr/interrupt.h>

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"


void (*ADC_CallBackPtr)(void) = NULL_PTR;


/*ADC Enable or Disable*/
Std_ReturnType MCAL_ADC_ADCInitStatus(uint8 Copy_ADCStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_ADCStatus != ADC_ENABLE &&
	   Copy_ADCStatus != ADC_DISABLE)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		ADCSRA_REG.ADEN_Bit7 = Copy_ADCStatus;
		ADC_OBJ.ADCStatus = Copy_ADCStatus;
		ADC_Private_OBJ.ADCStatus = Copy_ADCStatus;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_ADC_ADCChannelSelect(ADC_Input_Channel_t Copy_RequiredChannel)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_RequiredChannel > GND_Channel || Copy_RequiredChannel < ADC0_Channel ||
	   Copy_RequiredChannel == IGNORED_1  || Copy_RequiredChannel == IGNORED_2   ||
	   Copy_RequiredChannel == IGNORED_3  || Copy_RequiredChannel == IGNORED_4   ||
	   Copy_RequiredChannel == IGNORED_5  || Copy_RequiredChannel == IGNORED_6)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		ADMUX_REG.MUX_Bits = Copy_RequiredChannel;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_ADC_ADCResultAdjust(uint8 Copy_ResultAdjustment)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if( Copy_ResultAdjustment != ADC_RIGHT_ADJUST &&
	    Copy_ResultAdjustment != ADC_LEFT_ADJUST)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		ADMUX_REG.ADLAR_Bit5 = Copy_ResultAdjustment;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_ADC_ADCReferenceSelect(VREF_t Copy_RequiredVREF)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_RequiredVREF == IGNORED)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		ADMUX_REG.REFS_Bits = Copy_RequiredVREF;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

/*This API must be used to start conversion for both Single Conversion and Free Running modes*/
Std_ReturnType MCAL_ADC_ADCFirstConversionStart()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	ADCSRA_REG.ADSC_Bit6 = SET;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_ADC_ADCTriggerMode(ADC_Trigger_Source_t Copy_TriggerSource)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_TriggerSource == Single_Conversion)
	{
		ADCSRA_REG.ADATE_Bit5 = CLEAR;
		Local_ErrorStatus = E_OK;
	}
	else
	{
		if(ADCSRA_REG.ADATE_Bit5 != SET)
		{
			ADCSRA_REG.ADATE_Bit5 = SET;
		}
		SFIOR_REG_ADC.ADTS_Bits   =  Copy_TriggerSource;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_ADC_ADCPrescalarSelect(ADC_Prescalar_t Copy_ADCPrescalar)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	ADCSRA_REG.ADPS_Bits = Copy_ADCPrescalar;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

/*An API to read the data in the ADC Data Registers*/
Std_ReturnType MCAL_ADC_ADCReadResult(ADC_Input_Channel_t Copy_RequiredChannel ,uint16 *Copy_ADCResult)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	//In case of using proteus simulation enable this statements
	//MCAL_ADC_ADCChannelSelect(Copy_RequiredChannel);
	//MCAL_ADC_ADCFirstConversionStart();
	uint32 Local_U32_Counter = 0;
	while(Local_U32_Counter < 20000000)
	{
		Local_U32_Counter++;
		if(ADCSRA_REG.ADIF_Bit4 == ADC_STILL_FINISHED)
		{
			break;
		}
	}
	if(ADC_Private_OBJ.ADC_ResultAdjustment == ADC_RIGHT_ADJUST)
	{
		*Copy_ADCResult = (uint16)ADCL_REG;
		*Copy_ADCResult |= (( (uint16)ADCH_REG ) << 8);
		Local_ErrorStatus = E_OK;
	}
	else if(ADC_Private_OBJ. ADC_ResultAdjustment == ADC_LEFT_ADJUST)
	{
		*Copy_ADCResult = (( (uint8)ADCL_REG ) >> 6);
		*Copy_ADCResult |= (( (uint16)ADCH_REG ) << 2);
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}


/*ADC Interrupt APIs*/
Std_ReturnType MCAL_ADC_ADCInterruptStatus(uint8 Copy_INTStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_INTStatus != ADC_INT_DISABLE &&
	   Copy_INTStatus != ADC_INT_ENABLE)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		ADCSRA_REG.ADIE_Bit3 = Copy_INTStatus;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_ADC_ADCINTFlagRead(uint8 *Copy_INTFlagValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_INTFlagValue = ADCSRA_REG.ADIF_Bit4;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_ADC_ADCINTFlagClear()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	ADCSRA_REG.ADIF_Bit4 = CLEAR;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

//SetCallBack function
Std_ReturnType MCAL_ADC_ADCSetCallBack(void (*Copy_CallBackPtr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	ADC_CallBackPtr = Copy_CallBackPtr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

/*An API to update the informations in the configuration struct by user*/
Std_ReturnType MCAL_ADC_ADCOBJUpdate()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	ADC_OBJ.ADCStatus = ADC_Private_OBJ.ADCStatus;
	ADC_OBJ.ADC_CurrentChannel = ADC_Private_OBJ.ADC_CurrentChannel;
	ADC_OBJ.ADC_INTStatus = ADC_Private_OBJ.ADC_INTStatus;
	ADC_OBJ.ADC_ResultAdjustment = ADC_Private_OBJ.ADC_ResultAdjustment;
	ADC_OBJ.Trigger_Source = ADC_Private_OBJ.Trigger_Source;
	ADC_OBJ.VREF_Source = ADC_Private_OBJ.VREF_Source;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}


ISR(ADC_vect)
{
	ADC_CallBackPtr();
}
