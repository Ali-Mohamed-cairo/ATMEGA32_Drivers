/*
 * ADC_Interface.h
 *
 *  Created on: Jul 14, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

/*********************************Required Enums**********************************/

typedef enum{
	ADC0_Channel = 0,
	ADC1_Channel,
	ADC2_Channel,
	ADC3_Channel,
	ADC4_Channel,
	ADC5_Channel,
	ADC6_Channel,
	ADC7_Channel,
	/*Differential inputs: <POSIn>_<NEGIn>_Channel_<Gain>*/
	IGNORED_1,
	ADC1_ADC0_Channel_10,
	IGNORED_2,
	ADC1_ADC0_Channel_200,
	IGNORED_3,
	ADC3_ADC0_Channel_10,
	IGNORED_4,
	ADC3_ADC2_Channel_200,
	ADC0_ADC1_Channel_1,
	IGNORED_5,
	ADC2_ADC1_Channel_1,
	ADC3_ADC1_Channel_1,
	ADC4_ADC1_Channel_1,
	ADC5_ADC1_Channel_1,
	ADC6_ADC1_Channel_1,
	ADC7_ADC1_Channel_1,
	ADC0_ADC2_Channel_1,
	ADC1_ADC2_Channel_1,
	IGNORED_6,
	ADC3_ADC2_Channel_1,
	ADC4_ADC2_Channel_1,
	ADC5_ADC2_Channel_1,
	/*Special channels*/
	VBG_Channel,
	GND_Channel
}ADC_Input_Channel_t;

typedef enum{
	AREF = 0,
	AVCC,
	IGNORED,
	Internal_2_56
}VREF_t;

typedef enum{
	AUTO_FreeRunning = 0, /*First conversion need to be forced using: MCAL_ADC_ADCFirstConversionStart*/
	AUTO_Analog_Comparator,
	AUTO_EXTINT0,
	AUTO_TMR0_CompareMatch,
	AUTO_TMR0_Overflow,
	AUTO_TMR_CompareMatchB,
	AUTO_TMR1_CompareMatch,
	AUTO_TMR1_Overflow,
	Single_Conversion /*First conversion need to be forced using: MCAL_ADC_ADCFirstConversionStart*/
}ADC_Trigger_Source_t;


typedef enum{
	Div_2 = 1,
	Div_4,
	Div_8,
	Div_16,
	Div_32,
	Div_64,
	Div_128
}ADC_Prescalar_t;

/*This struct object will hold the current configurations about ADC.
 * Any update on the ADC hardware configurations will be updated here automatically.
 * Never overwrite on this struct members by yourself. If happened, update the latest
 * configurations using the API: MCAL_ADC_ADCOBJUpdate
 * */
struct{
	uint8 ADCStatus                    : 1;
	ADC_Input_Channel_t ADC_CurrentChannel;
	uint8 ADC_ResultAdjustment         : 1;
	VREF_t VREF_Source;
	ADC_Trigger_Source_t Trigger_Source;
	uint8 ADC_INTStatus                : 1;
}ADC_OBJ;

/**********************************Needed Macros*********************************/
/*<ADC status>*/
#define ADC_DISABLE          0
#define ADC_ENABLE           1

/*<ADC Interrupt status>*/
#define ADC_INT_DISABLE      0
#define ADC_INT_ENABLE       1

/*<ADC result adjustment>*/
#define ADC_RIGHT_ADJUST     0
#define ADC_LEFT_ADJUST      1


/*****************************************APIs*********************************/
Std_ReturnType MCAL_ADC_ADCInitStatus(uint8 Copy_ADCStatus);/*ADC Enable or Disable*/
Std_ReturnType MCAL_ADC_ADCChannelSelect(ADC_Input_Channel_t Copy_RequiredChannel);
Std_ReturnType MCAL_ADC_ADCResultAdjust(uint8 Copy_ResultAdjustment);
Std_ReturnType MCAL_ADC_ADCReferenceSelect(VREF_t Copy_RequiredVREF);
Std_ReturnType MCAL_ADC_ADCFirstConversionStart();/*This API must be used to start conversion for both Single Conversion and Free Running modes*/
Std_ReturnType MCAL_ADC_ADCTriggerMode(ADC_Trigger_Source_t Copy_TriggerSource);
Std_ReturnType MCAL_ADC_ADCPrescalarSelect(ADC_Prescalar_t Copy_ADCPrescalar);
/*An API to read the data in the ADC Data Registers*/
Std_ReturnType MCAL_ADC_ADCReadResult(ADC_Input_Channel_t Copy_RequiredChannel ,uint16 *Copy_ADCResult);
/*ADC Interrupt APIs*/
Std_ReturnType MCAL_ADC_ADCInterruptStatus(uint8 Copy_INTStatus);
Std_ReturnType MCAL_ADC_ADCINTFlagRead(uint8 *Copy_INTFlagValue);
Std_ReturnType MCAL_ADC_ADCINTFlagClear();
//SetCallBack function
Std_ReturnType MCAL_ADC_ADCSetCallBack(void (*Copy_CallBackPtr)(void));

/*An API to update the informations in the configuration struct by user*/
Std_ReturnType MCAL_ADC_ADCOBJUpdate();

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
