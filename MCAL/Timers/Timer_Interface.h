/*
 * Timer_interface.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_TIMERS_TIMER_INTERFACE_H_
#define MCAL_TIMERS_TIMER_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

#define INTERRUPT_DISABLE            0
#define INTERRUPT_ENABLE             1

typedef enum{
	Normal_Port_Operation_No_Waveform = 0, //No output @ OC0/PB3 pin.
	Toggle_OC_Pin_On_Compare_Match,
	Clear_OC_Pin_On_Compare_Match,
	Set_OC_Pin_On_Compare_Match
}CTC_Out_Waveform_t;

typedef enum{
	Timer_Counter_Stopped = 0,
	Timer_CLK_No_Prescaling,
	Timer_CLK_Div_8,
	Timer_CLK_Div_64,
	Timer_CLK_Div_256,
	Timer_CLK_Div_1024,
	Counter_EXT_Falling_Edge,
	Counter_EXT_Rising_Edge
}Clock_Source_Select_t;

/********************************************Timer/Counter0***************************************************/
//In case of using this timer as a counter, the input should be connected to T0/PB0 pin.
/*The output waveform -in case of using modes of operations which will give an output waveform- is visible on OC0/PB3 pin
 * and this pin is configured automatically by the APIs: MCAL_Timers_TMR0CTCModeSetup, MCAL_Timers_TMR0FastPWMModeSetup
 * , & MCAL_Timers_TMR0PhaseCorrectPWMModeSetup, as output pin.
 * */
/* To use the Timer/Counter0 follow the following steps:
 * 1- Configure the whole system clock frequency from the Timer_Config.h file.
 * 2- Use the MCAL_Timers_TMR0Init API choosing the required operation mode.
 * 3- If CTC, Fast-PWM, or Phase-Correct PWM, use the corresponding Setup API to complete your options.
 * 4- If you will use the interrupt, then enable it using the Interrupt APIs (Don't forget the SetCallBack).
 * 5- Use MCAL_Timers_TMR0Start to choose the required timer clock source and start timer/counter counts. If you want
 * 	  to stop timer use the function MCAL_Timers_TMR0Stop.
 * */

typedef enum{
	TMR0_Normal = 0,
	TMR0_Phase_Correct_PWM,
	TMR0_CTC,
	TMR0_FastPWM
}TMR0_Operate_Mode_t;

typedef enum{
	Normal_Port_Operation_No_PWM = 0, //No output @ OC0/PB3 pin.
	Non_Inverted_PWM = 2,
	//For Fast PWM => Clear OC0 on compare match, set OC0 at MAX
	//For Phase correct PWM => Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting
	Inverted_PWM
	//For Fast PWM => Set OC0 on compare match, clear OC0 at MAX
	//For Phase correct PWM => Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting
}Out_PWM_Waveform_t;

/****************<APIs>****************/
Std_ReturnType MCAL_Timers_TMR0Init(TMR0_Operate_Mode_t Copy_OperationMode);
Std_ReturnType MCAL_Timers_TMR0SetInitValue(uint8 Copy_TMR0InitValue);
Std_ReturnType MCAL_Timers_TMR0CTCModeSetup(uint8 Copy_CompareMatchValue, CTC_Out_Waveform_t Copy_WaveformSetup);
Std_ReturnType MCAL_Timers_TMR0FastPWMModeSetup(uint8 Copy_DutyCycle, Out_PWM_Waveform_t Copy_WaveformSetup);
Std_ReturnType MCAL_Timers_TMR0PhaseCorrectPWMModeSetup(uint8 Copy_DutyCycle, Out_PWM_Waveform_t Copy_WaveformSetup);
Std_ReturnType MCAL_Timers_TMR0Start(Clock_Source_Select_t Copy_CLKSource);
Std_ReturnType MCAL_Timers_TMR0Stop();
Std_ReturnType MCAL_Timers_TMR0ForceCompareMatch();

//TMR0 interrupt APIs
Std_ReturnType MCAL_Timers_TMR0OverflowInterruptStatus(uint8 Copy_InterruptStatus);
Std_ReturnType MCAL_Timers_TMR0ReadOverflowInterruptFlag(uint8 *Copy_OverflowInterruptFlag);
Std_ReturnType MCAL_Timers_TMR0ClearOverflowInterruptFlag();
Std_ReturnType MCAL_Timers_TMR0CompareMatchInterruptStatus(uint8 Copy_InterruptStatus);
Std_ReturnType MCAL_Timers_TMR0ReadCompareMatchInterruptFlag(uint8 *Copy_CompareMatchInterruptFlag);
Std_ReturnType MCAL_Timers_TMR0ClearCompareMatchInterruptFlag();
Std_ReturnType MCAL_Timers_TMR0OverlowSetCallBack(void (*Copy_PtrCallBack)(void));
Std_ReturnType MCAL_Timers_TMR0CompareMatchSetCallBack(void (*Copy_PtrCallBack)(void));

//Important time APIs
//If operating on 16MHz oscillator, then the maximum requested  time per code statement is: 268000 msec = 268 seconds = 4.4 minutes otherwise variables overflow will occur.
Std_ReturnType MCAL_Timers_TMR0Delay_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_DelayTime);
Std_ReturnType MCAL_Timers_TMR0Timer_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_TimerStopValue);



/********************************************Timer/Counter1***************************************************/
//In case of using this timer as a counter, the input should be connected to T1/PB1 pin.
/*The output waveform -in case of using modes of operations which will give an output waveform- is visible on either OC1A/PD5
 *or OC1B/PD4 pins according to the used channel * and these pins are configured automatically by the APIs: MCAL_Timers_TMR1CTCModeSetup, MCAL_Timers_TMR1FastPWMModeSetup
 * , & MCAL_Timers_TMR1PhaseCorrectPWMModeSetup, as output pins.
 * */

typedef enum{
	TMR1_Normal = 0,
	TMR1_Phase_Correct_PWM_8_BIT,
	TMR1_Phase_Correct_PWM_9_BIT,
	TMR1_Phase_Correct_PWM_10_BIT,
	TMR1_CTC_Output_Compare,
	TMR1_FastPWM_8_BIT,
	TMR1_FastPWM_9_BIT,
	TMR1_FastPWM_10_BIT,
	TMR1_Phase_Freq_Correct_Input_Capture,
	TMR1_Phase_Freq_Correct_Output_Compare,
	TMR1_Phase_Correct_Input_Capture,
	TMR1_Phase_Correct_Output_Compare,
	TMR1_CTC_Input_Capture,
	RESERVED,
	TMR1_FastPWM_Input_Capture,
	TMR1_FastPWM_Output_Compare
}TMR1_Operate_Mode_t;

typedef enum{
	TMR1_Channel_A,
	TMR1_Channel_B,
	TMR1_Channel_Input_Capture
}TMR1_Channel_Select_t;

typedef enum{
	TMR1_Normal_Port_Operation_No_PWM = 0, //No output @ OC1A/PD5 or OC1B/PD4 pins.
	TMR1_Toggle_OC1A_Pin,
	/*This mode for the generated waveform is allowed only of the following PWM modes:
	* 1- TMR1_Phase_Freq_Correct_Output_Compare.
	* 2- TMR1_FastPWM_Input_Capture.
	* 3- TMR1_FastPWM_Output_Compare.
	* This mode gives constant 50% duty cycle.
	*/
	TMR1_Non_Inverted_PWM = 2,
	//For Fast PWM => Clear OC1A/PD5 or OC1B/PD4 on compare match, set OC1A/PD5 or OC1B/PD4 at MAX
	//For Phase correct PWM => Clear OC0 on compare match when up-counting. Set OC0 on compare match when down-counting
	TMR1_Inverted_PWM
	//For Fast PWM => Set OC1A/PD5 or OC1B/PD4 on compare match, clear OC1A/PD5 or OC1B/PD4 at MAX
	//For Phase correct PWM => Set OC1A/PD5 or OC1B/PD4 on compare match when up-counting. Clear OC1A/PD5 or OC1B/PD4 on compare match when down-counting
}TMR1_Out_PWM_Waveform_t;

typedef enum{
	IC_FALLING_EDGE = 0,
	IC_RISIGN_EDGE
}TMR1_Input_Capture_Edge_Select_t;

typedef enum{
	IC_NC_DISABLE = 0,
	IC_NC_ENABLE
}TMR1_IC_Noise_Cancler_t;

/****************<APIs>****************/
Std_ReturnType MCAL_Timers_TMR1Init(TMR1_Operate_Mode_t Copy_OperationMode);
Std_ReturnType MCAL_Timers_TMR1SetInitValue(uint16 Copy_TMR1InitValue);
Std_ReturnType MCAL_Timers_TMR1CTCModeSetup(uint8 Copy_CompareMatchValue, TMR1_Channel_Select_t Copy_Channel, CTC_Out_Waveform_t Copy_WaveformSetup);
/*For both MCAL_Timers_TMR1FastPWMModeSetup and MCAL_Timers_TMR1PhaseCorrectPWMModeSetup, if you are using the Input
 * Capture Register 1 (ICR1) as the TOP value of Timer/Counter1, then fill the Copy_DutyCycle parameter with the
 * compare match value (TOP) which you want.
 * */
Std_ReturnType MCAL_Timers_TMR1FastPWMModeSetup(uint16 Copy_DutyCycle, TMR1_Channel_Select_t Copy_Channel, TMR1_Out_PWM_Waveform_t Copy_WaveformSetup);
Std_ReturnType MCAL_Timers_TMR1PhaseCorrectPWMModeSetup(uint16 Copy_DutyCycle, TMR1_Channel_Select_t Copy_Channel, Out_PWM_Waveform_t Copy_WaveformSetup);
Std_ReturnType MCAL_Timers_TMR1InputCaptureSetup(TMR1_Input_Capture_Edge_Select_t Copy_CaptureEdge, TMR1_IC_Noise_Cancler_t Copy_NCStatus);
Std_ReturnType MCAL_Timers_TMR1Start(Clock_Source_Select_t Copy_CLKSource);
Std_ReturnType MCAL_Timers_TMR1Stop();
Std_ReturnType MCAL_Timers_TMR1ForceCompareMatch(TMR1_Channel_Select_t Copy_Channel);

//TMR1 interrupt APIs
Std_ReturnType MCAL_Timers_TMR1OverflowInterruptStatus(uint8 Copy_InterruptStatus);
Std_ReturnType MCAL_Timers_TMR1ReadOverflowInterruptFlag(uint8 *Copy_OverflowInterruptFlag);
Std_ReturnType MCAL_Timers_TMR1ClearOverflowInterruptFlag();
Std_ReturnType MCAL_Timers_TMR1CompareMatchInterruptStatus(TMR1_Channel_Select_t Copy_Channel, uint8 Copy_InterruptStatus);
Std_ReturnType MCAL_Timers_TMR1ReadCompareMatchInterruptFlag(TMR1_Channel_Select_t Copy_Channel, uint8 *Copy_CompareMatchInterruptFlag);
Std_ReturnType MCAL_Timers_TMR1ClearCompareMatchInterruptFlag(TMR1_Channel_Select_t Copy_Channel);
Std_ReturnType MCAL_Timers_TMR1OverlowSetCallBack(void (*Copy_PtrCallBack)(void));
Std_ReturnType MCAL_Timers_TMR1CompareMatchChannel_A_SetCallBack(void (*Copy_PtrCallBack)(void));
Std_ReturnType MCAL_Timers_TMR1CompareMatchChannel_B_SetCallBack(void (*Copy_PtrCallBack)(void));
Std_ReturnType MCAL_Timers_TMR1CompareMatchChannel_IC_SetCallBack(void (*Copy_PtrCallBack)(void)); //For Input Capture(IC)

//Important time APIs
//If operating on 16MHz oscillator, then the maximum requested  time per code statement is: 268000 msec = 268 seconds = 4.4 minutes otherwise variables overflow will occur.
Std_ReturnType MCAL_Timers_TMR1Delay_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_DelayTime);
Std_ReturnType MCAL_Timers_TMR1Timer_ms(Clock_Source_Select_t Copy_CLKSource, uint32 Copy_TimerStopValue);


/********************************************Timer/Counter2***************************************************/

#endif /* MCAL_TIMERS_TIMER_INTERFACE_H_ */
