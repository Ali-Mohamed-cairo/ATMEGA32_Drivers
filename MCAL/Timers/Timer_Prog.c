/*
 * Timer_Prog.c
 *
 *  Created on: Nov 30, 2024
 *      Author: Ali Mohamed
 */

#include <avr/interrupt.h>

#include "../MCAL/GIE/GIE_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

#include "Timer_Interface.h"
#include "Timer_Private.h"
#include "Timer_Config.h"

/********************************************Timer/Counter0***************************************************/
static uint8  Global_TMR0CurrentOperationMode  = 0;
static uint32 Global_Timers_TMR0NoIterations   = 0;
static uint8  Global_Timers_TMR0DelayOperation = 0;
void (*Timers_TMR0PtrOverflowSetCallBack)(void)     = NULL_PTR;
void (*Timers_TMR0PtrCompareMatchSetCallBack)(void) = NULL_PTR;

Std_ReturnType MCAL_Timers_TMR0Init(TMR0_Operate_Mode_t Copy_OperationMode)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	switch(Copy_OperationMode)
	{
	case TMR0_Normal:
		TCCR0_REG.WGM00_Bit6 = CLEAR;
		TCCR0_REG.WGM01_Bit3 = CLEAR;
		TCCR0_REG.COM0_BITs = TMR0_Normal;
		Global_TMR0CurrentOperationMode = TMR0_Normal;
		Local_ErrorStatus = E_OK;
		break;
	case TMR0_Phase_Correct_PWM:
		TCCR0_REG.WGM00_Bit6 = SET;
		TCCR0_REG.WGM01_Bit3 = CLEAR;
		TCCR0_REG.FOC0_Bit7 = CLEAR;
		Global_TMR0CurrentOperationMode = TMR0_Phase_Correct_PWM;
		Local_ErrorStatus = E_OK;
		break;
	case TMR0_CTC:
		TCCR0_REG.WGM00_Bit6 = CLEAR;
		TCCR0_REG.WGM01_Bit3 = SET;
		Global_TMR0CurrentOperationMode = TMR0_CTC;
		Local_ErrorStatus = E_OK;
		break;
	case TMR0_FastPWM:
		TCCR0_REG.WGM00_Bit6 = SET;
		TCCR0_REG.WGM01_Bit3 = SET;
		TCCR0_REG.FOC0_Bit7 = CLEAR;
		Global_TMR0CurrentOperationMode = TMR0_FastPWM;
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0SetInitValue(uint8 Copy_TMR0InitValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TCNT0_REG = Copy_TMR0InitValue;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0CTCModeSetup(uint8 Copy_CompareMatchValue, CTC_Out_Waveform_t Copy_WaveformSetup)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Global_TMR0CurrentOperationMode != TMR0_CTC)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		OCR0_REG = Copy_CompareMatchValue;
		if((Copy_WaveformSetup > Normal_Port_Operation_No_Waveform) && (Copy_WaveformSetup <= Set_OC_Pin_On_Compare_Match))
		{
			Pin_Conig_t Local_OC0Pin = {.PORT_ID = DIO_PORTA, .Pin_Num = DIO_PIN3, .Pin_Direction = DIO_PIN_OUTPUT};
			MCAL_DIO_SetPinDirection(&Local_OC0Pin);
		}
		switch(Copy_WaveformSetup)
		{
		case Normal_Port_Operation_No_Waveform:
			TCCR0_REG.COM0_BITs = Normal_Port_Operation_No_Waveform;
			Local_ErrorStatus = E_OK;
			break;
		case Toggle_OC_Pin_On_Compare_Match:
			TCCR0_REG.COM0_BITs = Toggle_OC_Pin_On_Compare_Match;
			Local_ErrorStatus = E_OK;
			break;
		case Clear_OC_Pin_On_Compare_Match:
			TCCR0_REG.COM0_BITs = Clear_OC_Pin_On_Compare_Match;
			Local_ErrorStatus = E_OK;
			break;
		case Set_OC_Pin_On_Compare_Match:
			TCCR0_REG.COM0_BITs = Set_OC_Pin_On_Compare_Match;
			Local_ErrorStatus = E_OK;
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0FastPWMModeSetup(uint8 Copy_DutyCycle, Out_PWM_Waveform_t Copy_WaveformSetup)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Global_TMR0CurrentOperationMode != TMR0_FastPWM)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		if((Copy_WaveformSetup == Non_Inverted_PWM) || (Copy_WaveformSetup == Inverted_PWM))
		{
			Pin_Conig_t Local_OC0Pin = {.PORT_ID = DIO_PORTA, .Pin_Num = DIO_PIN3, .Pin_Direction = DIO_PIN_OUTPUT};
			MCAL_DIO_SetPinDirection(&Local_OC0Pin);
		}
		switch(Copy_WaveformSetup)
		{
		case Normal_Port_Operation_No_PWM:
			TCCR0_REG.COM0_BITs = Normal_Port_Operation_No_PWM;
			Local_ErrorStatus = E_OK;
			break;
		case Non_Inverted_PWM:
			OCR0_REG = ((Copy_DutyCycle/100) * (TMR0_MAX+1)) - 1;
			TCCR0_REG.COM0_BITs = Non_Inverted_PWM;
			Local_ErrorStatus = E_OK;
			break;
		case Inverted_PWM:
			OCR0_REG = TMR0_MAX - ((Copy_DutyCycle/100) * (TMR0_MAX+1)) + 1;
			TCCR0_REG.COM0_BITs = Inverted_PWM;
			Local_ErrorStatus = E_OK;
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0PhaseCorrectPWMModeSetup(uint8 Copy_DutyCycle, Out_PWM_Waveform_t Copy_WaveformSetup)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Global_TMR0CurrentOperationMode != TMR0_Phase_Correct_PWM)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		if((Copy_WaveformSetup == Non_Inverted_PWM) || (Copy_WaveformSetup == Inverted_PWM))
		{
			Pin_Conig_t Local_OC0Pin = {.PORT_ID = DIO_PORTA, .Pin_Num = DIO_PIN3, .Pin_Direction = DIO_PIN_OUTPUT};
			MCAL_DIO_SetPinDirection(&Local_OC0Pin);
		}
		switch(Copy_WaveformSetup)
		{
		case Normal_Port_Operation_No_PWM:
			TCCR0_REG.COM0_BITs = Normal_Port_Operation_No_PWM;
			Local_ErrorStatus = E_OK;
			break;
		case Non_Inverted_PWM:
			OCR0_REG = (((Copy_DutyCycle/100) * (2*TMR0_MAX + 1)) - 1) / 2;
			TCCR0_REG.COM0_BITs = Non_Inverted_PWM;
			Local_ErrorStatus = E_OK;
			break;
		case Inverted_PWM:
			OCR0_REG = TMR0_MAX - ((((Copy_DutyCycle/100) * (2*TMR0_MAX + 1)) - 1) / 2);
			TCCR0_REG.COM0_BITs = Inverted_PWM;
			Local_ErrorStatus = E_OK;
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0Start(Clock_Source_Select_t Copy_CLKSource)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_CLKSource == Timer_Counter_Stopped)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		TCCR0_REG.CS0_BITs = Copy_CLKSource;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0Stop()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TCCR0_REG.CS0_BITs = Timer_Counter_Stopped;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0ForceCompareMatch()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if((Global_TMR0CurrentOperationMode == TMR0_Normal) || (Global_TMR0CurrentOperationMode == TMR0_CTC))
	{
		TCCR0_REG.FOC0_Bit7 = SET;
		Local_ErrorStatus = E_OK;
	}
	else
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	return Local_ErrorStatus;
}

//TMR0 interrupt APIs
Std_ReturnType MCAL_Timers_TMR0OverflowInterruptStatus(uint8 Copy_InterruptStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TIMSK_REG.TOIE0_Bit0 = Copy_InterruptStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0ReadOverflowInterruptFlag(uint8 *Copy_OverflowInterruptFlag)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_OverflowInterruptFlag = TIFR_REG.TOV0_Bit0;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0ClearOverflowInterruptFlag()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TIFR_REG.TOV0_Bit0 = SET;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0CompareMatchInterruptStatus(uint8 Copy_InterruptStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TIMSK_REG.OCIE0_Bit1 = Copy_InterruptStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0ReadCompareMatchInterruptFlag(uint8 *Copy_CompareMatchInterruptFlag)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_CompareMatchInterruptFlag = TIFR_REG.OCF0_Bit1;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0ClearCompareMatchInterruptFlag()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TIFR_REG.OCF0_Bit1 = SET;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0OverlowSetCallBack(void (*Copy_PtrCallBack)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Timers_TMR0PtrOverflowSetCallBack = Copy_PtrCallBack;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0CompareMatchSetCallBack(void (*Copy_PtrCallBack)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Timers_TMR0PtrCompareMatchSetCallBack = Copy_PtrCallBack;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

//Important time APIs
Std_ReturnType MCAL_Timers_TMR0Delay_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_DelayTime)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint32 Local_TimerFreq = 0;
	uint32 Local_NumTicks = 0;
	uint32 Local_NumExtraIteractions = 0;
	uint32 Local_NumExtraTicks = 0;
	Global_Timers_TMR0DelayOperation = SET;
	MCAL_Timers_TMR0Init(TMR0_Normal);
	switch(Copy_CLKSource)
	{
	case Timer_CLK_No_Prescaling:
		Local_TimerFreq = FREQ_SYSTEM_CLK;
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_8:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/8);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_64:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/64);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_256:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/256);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_1024:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/1024);
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	if(Local_ErrorStatus == E_OK)
	{
		Local_NumTicks = (Copy_DelayTime/1000)*Local_TimerFreq;
		Global_Timers_TMR0NoIterations = Local_NumTicks / (TMR0_MAX + 1);
		Local_NumExtraIteractions = ((float64)Local_NumTicks / (TMR0_MAX + 1)) - Global_Timers_TMR0NoIterations;
		Local_NumExtraTicks = TMR0_MAX - (TMR0_MAX * Local_NumExtraIteractions);
		MCAL_Timers_TMR0SetInitValue(Local_NumExtraTicks);
		MCAL_Timers_TMR0OverflowInterruptStatus(INTERRUPT_ENABLE);
		MCAL_Timers_TMR0Start(Copy_CLKSource);
		for(; Global_Timers_TMR0NoIterations > 0;)
		{
			while(Global_Timers_TMR0DelayOperation == SET);
		}
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR0Timer_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_TimerStopValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint32 Local_TimerFreq = 0;
	uint32 Local_NumTicks = 0;
	uint32 Local_NumExtraIteractions = 0;
	uint32 Local_NumExtraTicks = 0;
	MCAL_Timers_TMR0Init(TMR0_Normal);
	switch(Copy_CLKSource)
	{
	case Timer_CLK_No_Prescaling:
		Local_TimerFreq = FREQ_SYSTEM_CLK;
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_8:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/8);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_64:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/64);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_256:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/256);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_1024:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/1024);
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	if(Local_ErrorStatus == E_OK)
	{
		Local_NumTicks = (Copy_TimerStopValue/1000)*Local_TimerFreq;
		Global_Timers_TMR0NoIterations = Local_NumTicks / (TMR0_MAX + 1);
		Local_NumExtraIteractions = ((float64)Local_NumTicks / (TMR0_MAX + 1)) - Global_Timers_TMR0NoIterations;
		Local_NumExtraTicks = TMR0_MAX - (TMR0_MAX * Local_NumExtraIteractions);
		MCAL_Timers_TMR0SetInitValue(Local_NumExtraTicks);
		MCAL_Timers_TMR0OverflowInterruptStatus(INTERRUPT_ENABLE);
		MCAL_Timers_TMR0Start(Copy_CLKSource);
	}
	return Local_ErrorStatus;
}

//TMR0 ISRs
ISR(TIMER0_OVF_vect)
{
	if(Global_Timers_TMR0NoIterations > 0)
	{
		--Global_Timers_TMR0NoIterations;
		if(Global_Timers_TMR0NoIterations == 0)
		{
			MCAL_Timers_TMR0Stop();
			if(Global_Timers_TMR0DelayOperation == SET) //If delay function is used
			{
				Global_Timers_TMR0DelayOperation = CLEAR;
			}
			else //If timer function is used
			{
				Timers_TMR0PtrOverflowSetCallBack();
			}
		}
	}
	else
	{
		Timers_TMR0PtrOverflowSetCallBack();
	}
}

ISR(TIMER0_COMP_vect)
{
	Timers_TMR0PtrCompareMatchSetCallBack();
}



/********************************************Timer/Counter1***************************************************/
static uint8  Global_TMR1CurrentOperationMode = 0;
static uint32 Global_Timers_TMR1NoIterations   = 0;
static uint8  Global_Timers_TMR1DelayOperation = 0;
void (*Timers_TMR1PtrOverflowSetCallBack)(void)     = NULL_PTR;
void (*Timers_TMR1PtrCompareMatchChannel_A_SetCallBack)(void) = NULL_PTR;
void (*Timers_TMR1PtrCompareMatchChannel_B_SetCallBack)(void) = NULL_PTR;
void (*Timers_TMR1PtrCompareMatchChannel_IC_SetCallBack)(void) = NULL_PTR;

Std_ReturnType MCAL_Timers_TMR1Init(TMR1_Operate_Mode_t Copy_OperationMode)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if((Copy_OperationMode == TMR1_Phase_Freq_Correct_Input_Capture) || (Copy_OperationMode == TMR1_Phase_Correct_Input_Capture) || (Copy_OperationMode == TMR1_CTC_Input_Capture))
	{
		Pin_Conig_t Local_ICP1Pin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN6, .Pin_Direction = DIO_PIN_INPUT};
		MCAL_DIO_SetPinDirection(&Local_ICP1Pin);
	}
	switch(Copy_OperationMode)
	{
	case TMR1_Normal:
		TCCR1A_REG.WGM1_1_0_BITs = CLEAR;
		TCCR1B_REG.WGM1_3_2_BITs = CLEAR;
		TCCR1A_REG.COM1A_BITs = TMR1_Normal;
		TCCR1A_REG.COM1B_BITs = TMR1_Normal;
		Global_TMR1CurrentOperationMode = TMR1_Normal;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Correct_PWM_8_BIT:
		TCCR1A_REG.WGM1_1_0_BITs = SET;
		TCCR1B_REG.WGM1_3_2_BITs = CLEAR;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Correct_PWM_8_BIT;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Correct_PWM_9_BIT:
		TCCR1A_REG.WGM1_1_0_BITs = 2;
		TCCR1B_REG.WGM1_3_2_BITs = CLEAR;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Correct_PWM_9_BIT;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Correct_PWM_10_BIT:
		TCCR1A_REG.WGM1_1_0_BITs = 3;
		TCCR1B_REG.WGM1_3_2_BITs = CLEAR;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Correct_PWM_10_BIT;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_CTC_Output_Compare:
		TCCR1A_REG.WGM1_1_0_BITs = CLEAR;
		TCCR1B_REG.WGM1_3_2_BITs = SET;
		Global_TMR1CurrentOperationMode = TMR1_CTC_Output_Compare;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_FastPWM_8_BIT:
		TCCR1A_REG.WGM1_1_0_BITs = SET;
		TCCR1B_REG.WGM1_3_2_BITs = SET;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_FastPWM_8_BIT;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_FastPWM_9_BIT:
		TCCR1A_REG.WGM1_1_0_BITs = 2;
		TCCR1B_REG.WGM1_3_2_BITs = SET;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_FastPWM_9_BIT;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_FastPWM_10_BIT:
		TCCR1A_REG.WGM1_1_0_BITs = 3;
		TCCR1B_REG.WGM1_3_2_BITs = SET;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_FastPWM_10_BIT;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Freq_Correct_Input_Capture:
		TCCR1A_REG.WGM1_1_0_BITs = CLEAR;
		TCCR1B_REG.WGM1_3_2_BITs = 2;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Freq_Correct_Input_Capture;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Freq_Correct_Output_Compare:
		TCCR1A_REG.WGM1_1_0_BITs = SET;
		TCCR1B_REG.WGM1_3_2_BITs = 2;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Freq_Correct_Output_Compare;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Correct_Input_Capture:
		TCCR1A_REG.WGM1_1_0_BITs = 2;
		TCCR1B_REG.WGM1_3_2_BITs = 2;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Correct_Input_Capture;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Phase_Correct_Output_Compare:
		TCCR1A_REG.WGM1_1_0_BITs = 3;
		TCCR1B_REG.WGM1_3_2_BITs = 2;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_Phase_Correct_Output_Compare;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_CTC_Input_Capture:
		TCCR1A_REG.WGM1_1_0_BITs = 0;
		TCCR1B_REG.WGM1_3_2_BITs = 3;
		Global_TMR1CurrentOperationMode = TMR1_CTC_Input_Capture;
		Local_ErrorStatus = E_OK;
		break;
	case RESERVED:
		Local_ErrorStatus = E_NOT_OK;
		break;
	case TMR1_FastPWM_Input_Capture:
		TCCR1A_REG.WGM1_1_0_BITs = 3;
		TCCR1B_REG.WGM1_3_2_BITs = 2;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_FastPWM_Input_Capture;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_FastPWM_Output_Compare:
		TCCR1A_REG.WGM1_1_0_BITs = 2;
		TCCR1B_REG.WGM1_3_2_BITs = 3;
		TCCR1A_REG.FOC1A_Bit3 = CLEAR;
		TCCR1A_REG.FOC1B_Bit2 = CLEAR;
		Global_TMR1CurrentOperationMode = TMR1_FastPWM_Output_Compare;
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1SetInitValue(uint16 Copy_TMR1InitValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_CurrentGIStatus      = CLEAR;
	//It's recommended to disable the interrupts when accessing 16-bit registers.
	MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
	MCAL_GlobalINTStatusWrite(GI_DISABLE);
	TCNT1_REG = Copy_TMR1InitValue;
	MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1CTCModeSetup(uint8 Copy_CompareMatchValue, TMR1_Channel_Select_t Copy_Channel, CTC_Out_Waveform_t Copy_WaveformSetup)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_CurrentGIStatus      = CLEAR;
	if((Global_TMR0CurrentOperationMode != TMR1_CTC_Output_Compare) && (Global_TMR0CurrentOperationMode != TMR1_CTC_Input_Capture))
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		switch(Copy_Channel)
		{
		case TMR1_Channel_A:
			//It's recommended to disable the interrupts when accessing 16-bit registers.
			MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
			MCAL_GlobalINTStatusWrite(GI_DISABLE);
			OCR1A_REG = Copy_CompareMatchValue;
			MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
			if((Copy_WaveformSetup > Normal_Port_Operation_No_Waveform) && (Copy_WaveformSetup <= Set_OC_Pin_On_Compare_Match))
			{
				Pin_Conig_t Local_OC1APin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN5, .Pin_Direction = DIO_PIN_OUTPUT};
				MCAL_DIO_SetPinDirection(&Local_OC1APin);
			}
			switch(Copy_WaveformSetup)
			{
			case Normal_Port_Operation_No_Waveform:
				TCCR1A_REG.COM1A_BITs = Normal_Port_Operation_No_Waveform;
				Local_ErrorStatus = E_OK;
				break;
			case Toggle_OC_Pin_On_Compare_Match:
				TCCR1A_REG.COM1A_BITs = Toggle_OC_Pin_On_Compare_Match;
				Local_ErrorStatus = E_OK;
				break;
			case Clear_OC_Pin_On_Compare_Match:
				TCCR1A_REG.COM1A_BITs = Clear_OC_Pin_On_Compare_Match;
				Local_ErrorStatus = E_OK;
				break;
			case Set_OC_Pin_On_Compare_Match:
				TCCR1A_REG.COM1A_BITs = Set_OC_Pin_On_Compare_Match;
				Local_ErrorStatus = E_OK;
				break;
			default:
				Local_ErrorStatus = E_NOT_OK;
				break;
			}
			break;
		case TMR1_Channel_B:
			//It's recommended to disable the interrupts when accessing 16-bit registers.
			MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
			MCAL_GlobalINTStatusWrite(GI_DISABLE);
			OCR1B_REG = Copy_CompareMatchValue;
			MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
			if((Copy_WaveformSetup > Normal_Port_Operation_No_Waveform) && (Copy_WaveformSetup <= Set_OC_Pin_On_Compare_Match))
			{
				Pin_Conig_t Local_OC1BPin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN4, .Pin_Direction = DIO_PIN_OUTPUT};
				MCAL_DIO_SetPinDirection(&Local_OC1BPin);
			}
			switch(Copy_WaveformSetup)
			{
			case Normal_Port_Operation_No_Waveform:
				TCCR1A_REG.COM1B_BITs = Normal_Port_Operation_No_Waveform;
				Local_ErrorStatus = E_OK;
				break;
			case Toggle_OC_Pin_On_Compare_Match:
				TCCR1A_REG.COM1B_BITs = Toggle_OC_Pin_On_Compare_Match;
				Local_ErrorStatus = E_OK;
				break;
			case Clear_OC_Pin_On_Compare_Match:
				TCCR1A_REG.COM1B_BITs = Clear_OC_Pin_On_Compare_Match;
				Local_ErrorStatus = E_OK;
				break;
			case Set_OC_Pin_On_Compare_Match:
				TCCR1A_REG.COM1B_BITs = Set_OC_Pin_On_Compare_Match;
				Local_ErrorStatus = E_OK;
				break;
			default:
				Local_ErrorStatus = E_NOT_OK;
				break;
			}
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1FastPWMModeSetup(uint16 Copy_DutyCycle, TMR1_Channel_Select_t Copy_Channel, TMR1_Out_PWM_Waveform_t Copy_WaveformSetup)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_CurrentGIStatus      = CLEAR;
	if(Global_TMR0CurrentOperationMode != TMR0_FastPWM)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		switch(Copy_Channel)
		{
		case TMR1_Channel_A:
			if((Copy_WaveformSetup > TMR1_Normal_Port_Operation_No_PWM) && (Copy_WaveformSetup <= TMR1_Inverted_PWM))
			{
				Pin_Conig_t Local_OC1APin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN5, .Pin_Direction = DIO_PIN_OUTPUT};
				MCAL_DIO_SetPinDirection(&Local_OC1APin);
			}
			switch(Copy_WaveformSetup)
			{
			case TMR1_Normal_Port_Operation_No_PWM:
				TCCR1A_REG.COM1A_BITs = TMR1_Normal_Port_Operation_No_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Toggle_OC1A_Pin:
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				/*  The stored value will not affect anything where this mode gives 50% duty cycle obligally
				   *so that we place the duty cycle as random number.
				 * */
				OCR1A_REG = Copy_DutyCycle;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1A_BITs = TMR1_Toggle_OC1A_Pin;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Non_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1A_REG = ((Copy_DutyCycle/100) * (TMR0_MAX+1)) - 1;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1A_BITs = TMR1_Non_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1A_REG = TMR0_MAX - ((Copy_DutyCycle/100) * (TMR0_MAX+1));
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1A_BITs = TMR1_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			default:
				Local_ErrorStatus = E_NOT_OK;
				break;
			}
			break;
		case TMR1_Channel_B:
			if((Copy_WaveformSetup > TMR1_Normal_Port_Operation_No_PWM) && (Copy_WaveformSetup <= TMR1_Inverted_PWM))
			{
				Pin_Conig_t Local_OC1BPin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN4, .Pin_Direction = DIO_PIN_OUTPUT};
				MCAL_DIO_SetPinDirection(&Local_OC1BPin);
			}
			switch(Copy_WaveformSetup)
			{
			case TMR1_Normal_Port_Operation_No_PWM:
				TCCR1A_REG.COM1B_BITs = TMR1_Normal_Port_Operation_No_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Toggle_OC1A_Pin:
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				/* * The stored value will not affect anything where this mode gives constant 50% duty cycle
				   *so that we place the duty cycle as random number.
				 * */
				OCR1B_REG = Copy_DutyCycle;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1B_BITs = TMR1_Toggle_OC1A_Pin;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Non_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1B_REG = ((Copy_DutyCycle/100) * (TMR0_MAX+1)) - 1;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1B_BITs = TMR1_Non_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1B_REG = TMR0_MAX - ((Copy_DutyCycle/100) * (TMR0_MAX+1));
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1B_BITs = TMR1_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			default:
				Local_ErrorStatus = E_NOT_OK;
				break;
			}
			break;
		case TMR1_Channel_Input_Capture:
			//It's recommended to disable the interrupts when accessing 16-bit registers.
			MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
			MCAL_GlobalINTStatusWrite(GI_DISABLE);
			ICR1_REG = Copy_DutyCycle; // Read the comment in Timer_Interface.h to know why Copy_DutyCycle is used.
			MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1PhaseCorrectPWMModeSetup(uint16 Copy_DutyCycle, TMR1_Channel_Select_t Copy_Channel, Out_PWM_Waveform_t Copy_WaveformSetup)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_CurrentGIStatus      = CLEAR;
	if(Global_TMR0CurrentOperationMode != TMR0_FastPWM)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		switch(Copy_Channel)
		{
		case TMR1_Channel_A:
			if((Copy_WaveformSetup > TMR1_Normal_Port_Operation_No_PWM) && (Copy_WaveformSetup <= TMR1_Inverted_PWM))
			{
				Pin_Conig_t Local_OC1APin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN5, .Pin_Direction = DIO_PIN_OUTPUT};
				MCAL_DIO_SetPinDirection(&Local_OC1APin);
			}
			switch(Copy_WaveformSetup)
			{
			case TMR1_Normal_Port_Operation_No_PWM:
				TCCR1A_REG.COM1A_BITs = TMR1_Normal_Port_Operation_No_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Toggle_OC1A_Pin:
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				/*  The stored value will not affect anything where this mode gives constant 50% duty cycle
				   *so that we place the duty cycle as random number.
				 * */
				OCR1A_REG = Copy_DutyCycle;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1A_BITs = TMR1_Toggle_OC1A_Pin;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Non_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1A_REG = (((Copy_DutyCycle/100) * (2*TMR0_MAX + 1)) - 1) / 2;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1A_BITs = TMR1_Non_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1A_REG = TMR0_MAX - ((((Copy_DutyCycle/100) * (2*TMR0_MAX + 1)) - 1) / 2);
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1A_BITs = TMR1_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			default:
				Local_ErrorStatus = E_NOT_OK;
				break;
			}
			break;
		case TMR1_Channel_B:
			if((Copy_WaveformSetup > TMR1_Normal_Port_Operation_No_PWM) && (Copy_WaveformSetup <= TMR1_Inverted_PWM))
			{
				Pin_Conig_t Local_OC1BPin = {.PORT_ID = DIO_PORTD, .Pin_Num = DIO_PIN4, .Pin_Direction = DIO_PIN_OUTPUT};
				MCAL_DIO_SetPinDirection(&Local_OC1BPin);
			}
			switch(Copy_WaveformSetup)
			{
			case TMR1_Normal_Port_Operation_No_PWM:
				TCCR1A_REG.COM1B_BITs = TMR1_Normal_Port_Operation_No_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Toggle_OC1A_Pin:
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				/* * The stored value will not affect anything where this mode gives constant 50% duty cycle
				   *so that we place the duty cycle as random number.
				 * */
				OCR1B_REG = Copy_DutyCycle;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1B_BITs = TMR1_Toggle_OC1A_Pin;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Non_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1B_REG = (((Copy_DutyCycle/100) * (2*TMR0_MAX + 1)) - 1) / 2;
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1B_BITs = TMR1_Non_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			case TMR1_Inverted_PWM:
				//It's recommended to disable the interrupts when accessing 16-bit registers.
				MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
				MCAL_GlobalINTStatusWrite(GI_DISABLE);
				OCR1B_REG = TMR0_MAX - ((((Copy_DutyCycle/100) * (2*TMR0_MAX + 1)) - 1) / 2);
				MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
				TCCR1A_REG.COM1B_BITs = TMR1_Inverted_PWM;
				Local_ErrorStatus = E_OK;
				break;
			default:
				Local_ErrorStatus = E_NOT_OK;
				break;
			}
			break;
		case TMR1_Channel_Input_Capture:
			//It's recommended to disable the interrupts when accessing 16-bit registers.
			MCAL_GlobalINTStatusRead(&Local_CurrentGIStatus);
			MCAL_GlobalINTStatusWrite(GI_DISABLE);
			ICR1_REG = Copy_DutyCycle; // Read the comment in Timer_Interface.h to know why Copy_DutyCycle is used.
			MCAL_GlobalINTStatusWrite(Local_CurrentGIStatus);
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1InputCaptureSetup(TMR1_Input_Capture_Edge_Select_t Copy_CaptureEdge, TMR1_IC_Noise_Cancler_t Copy_NCStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if((Copy_CaptureEdge == IC_FALLING_EDGE) || (Copy_CaptureEdge == IC_RISIGN_EDGE))
	{
		TCCR1B_REG.ICES1_Bit6 = Copy_CaptureEdge;
	}
	else
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	if((Copy_NCStatus == IC_NC_DISABLE) || (Copy_NCStatus == IC_NC_ENABLE))
	{
		TCCR1B_REG.ICNC1_Bit7 = Copy_NCStatus;
	}
	else
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1Start(Clock_Source_Select_t Copy_CLKSource)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_CLKSource == Timer_Counter_Stopped)
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		TCCR1B_REG.CS1_BITs = Copy_CLKSource;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_Timers_TMR1Stop()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TCCR1B_REG.CS1_BITs = Timer_Counter_Stopped;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}


Std_ReturnType MCAL_Timers_TMR1ForceCompareMatch(TMR1_Channel_Select_t Copy_Channel)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if((Global_TMR1CurrentOperationMode == TMR1_Normal) || (Global_TMR1CurrentOperationMode == TMR1_CTC_Output_Compare) || (Global_TMR1CurrentOperationMode == TMR1_CTC_Input_Capture))
	{
		switch(Copy_Channel)
		{
		case TMR1_Channel_A:
			TCCR1A_REG.FOC1A_Bit3 = SET;
			Local_ErrorStatus = E_OK;
			break;
		case TMR1_Channel_B:
			TCCR1A_REG.FOC1B_Bit2 = SET;
			Local_ErrorStatus = E_OK;
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	else
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	return Local_ErrorStatus;
}

//TMR1 interrupt APIs
Std_ReturnType MCAL_Timers_TMR1OverflowInterruptStatus(uint8 Copy_InterruptStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TIMSK_REG.TOIE1_Bit2 = Copy_InterruptStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1ReadOverflowInterruptFlag(uint8 *Copy_OverflowInterruptFlag)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_OverflowInterruptFlag = TIFR_REG.TOV1_Bit2;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1ClearOverflowInterruptFlag()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	TIFR_REG.TOV1_Bit2 = SET;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1CompareMatchInterruptStatus(TMR1_Channel_Select_t Copy_Channel, uint8 Copy_InterruptStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	switch(Copy_Channel)
	{
	case TMR1_Channel_A:
		TIMSK_REG.OCIE1A_Bit4 = Copy_InterruptStatus;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Channel_B:
		TIMSK_REG.OCIE1B_Bit3 = Copy_InterruptStatus;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Channel_Input_Capture:
		TIMSK_REG.TICIE1_Bit5 = Copy_InterruptStatus;
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1ReadCompareMatchInterruptFlag(TMR1_Channel_Select_t Copy_Channel, uint8 *Copy_CompareMatchInterruptFlag)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	switch(Copy_Channel)
	{
	case TMR1_Channel_A:
		*Copy_CompareMatchInterruptFlag = TIFR_REG.OCF1A_Bit4;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Channel_B:
		*Copy_CompareMatchInterruptFlag = TIFR_REG.OCF1B_Bit3;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Channel_Input_Capture:
		*Copy_CompareMatchInterruptFlag = TIFR_REG.ICF1_Bit5;
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1ClearCompareMatchInterruptFlag(TMR1_Channel_Select_t Copy_Channel)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	switch(Copy_Channel)
	{
	case TMR1_Channel_A:
		TIFR_REG.OCF1A_Bit4 = SET;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Channel_B:
		TIFR_REG.OCF1B_Bit3 = SET;
		Local_ErrorStatus = E_OK;
		break;
	case TMR1_Channel_Input_Capture:
		TIFR_REG.ICF1_Bit5 = SET;
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1OverlowSetCallBack(void (*Copy_PtrCallBack)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Timers_TMR1PtrOverflowSetCallBack = Copy_PtrCallBack;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1CompareMatchChannel_A_SetCallBack(void (*Copy_PtrCallBack)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Timers_TMR1PtrCompareMatchChannel_A_SetCallBack = Copy_PtrCallBack;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1CompareMatchChannel_B_SetCallBack(void (*Copy_PtrCallBack)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Timers_TMR1PtrCompareMatchChannel_B_SetCallBack = Copy_PtrCallBack;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1CompareMatchChannel_IC_SetCallBack(void (*Copy_PtrCallBack)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Timers_TMR1PtrCompareMatchChannel_IC_SetCallBack = Copy_PtrCallBack;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

//Important time APIs
Std_ReturnType MCAL_Timers_TMR1Delay_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_DelayTime)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint32 Local_TimerFreq = 0;
	uint32 Local_NumTicks = 0;
	uint32 Local_NumExtraIteractions = 0;
	uint32 Local_NumExtraTicks = 0;
	Global_Timers_TMR1DelayOperation = SET;
	MCAL_Timers_TMR1Init(TMR1_Normal);
	switch(Copy_CLKSource)
	{
	case Timer_CLK_No_Prescaling:
		Local_TimerFreq = FREQ_SYSTEM_CLK;
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_8:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/8);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_64:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/64);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_256:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/256);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_1024:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/1024);
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	if(Local_ErrorStatus == E_OK)
	{
		Local_NumTicks = (Copy_DelayTime/1000)*Local_TimerFreq;
		Global_Timers_TMR1NoIterations = Local_NumTicks / (TMR1_MAX + 1);
		Local_NumExtraIteractions = ((float64)Local_NumTicks / (TMR1_MAX + 1)) - Global_Timers_TMR1NoIterations;
		Local_NumExtraTicks = TMR1_MAX - (TMR1_MAX * Local_NumExtraIteractions);
		MCAL_Timers_TMR1SetInitValue(Local_NumExtraTicks);
		MCAL_Timers_TMR1OverflowInterruptStatus(INTERRUPT_ENABLE);
		MCAL_Timers_TMR1Start(Copy_CLKSource);
		for(; Global_Timers_TMR1NoIterations > 0;)
		{
			while(Global_Timers_TMR1DelayOperation == SET);
		}
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_Timers_TMR1Timer_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_TimerStopValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint32 Local_TimerFreq = 0;
	uint32 Local_NumTicks = 0;
	uint32 Local_NumExtraIteractions = 0;
	uint32 Local_NumExtraTicks = 0;
	MCAL_Timers_TMR1Init(TMR1_Normal);
	switch(Copy_CLKSource)
	{
	case Timer_CLK_No_Prescaling:
		Local_TimerFreq = FREQ_SYSTEM_CLK;
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_8:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/8);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_64:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/64);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_256:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/256);
		Local_ErrorStatus = E_OK;
		break;
	case Timer_CLK_Div_1024:
		Local_TimerFreq = (FREQ_SYSTEM_CLK/1024);
		Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}
	if(Local_ErrorStatus == E_OK)
	{
		Local_NumTicks = (Copy_TimerStopValue/1000)*Local_TimerFreq;
		Global_Timers_TMR1NoIterations = Local_NumTicks / (TMR1_MAX + 1);
		Local_NumExtraIteractions = ((float64)Local_NumTicks / (TMR1_MAX + 1)) - Global_Timers_TMR1NoIterations;
		Local_NumExtraTicks = TMR1_MAX - (TMR1_MAX * Local_NumExtraIteractions);
		MCAL_Timers_TMR1SetInitValue(Local_NumExtraTicks);
		MCAL_Timers_TMR1OverflowInterruptStatus(INTERRUPT_ENABLE);
		MCAL_Timers_TMR1Start(Copy_CLKSource);
	}
	return Local_ErrorStatus;
}


ISR(TIMER1_OVF_vect)
{
	if(Global_Timers_TMR1NoIterations > 0)
	{
		--Global_Timers_TMR1NoIterations;
		if(Global_Timers_TMR1NoIterations == 0)
		{
			MCAL_Timers_TMR0Stop();
			if(Global_Timers_TMR1DelayOperation == SET) //If delay function is used
			{
				Global_Timers_TMR1DelayOperation = CLEAR;
			}
			else //If timer function is used
			{
				Timers_TMR1PtrOverflowSetCallBack();
			}
		}
	}
	else
	{
		Timers_TMR1PtrOverflowSetCallBack();
	}
}

ISR(TIMER1_COMPA_vect)
{
	Timers_TMR1PtrCompareMatchChannel_A_SetCallBack();
}

ISR(TIMER1_COMPB_vect)
{
	Timers_TMR1PtrCompareMatchChannel_B_SetCallBack();
}

ISR(TIMER1_CAPT_vect)
{
	Timers_TMR1PtrCompareMatchChannel_IC_SetCallBack();
}
