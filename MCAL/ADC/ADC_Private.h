/*
 * ADC_Private.h
 *
 *  Created on: Jul 14, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_


typedef union{
	struct{
		uint8 MUX_Bits   : 5;
		uint8 ADLAR_Bit5 : 1;
		uint8 REFS_Bits  : 2;
	};
	uint8 ADMUX_Register;
}ADMUX_REG_t;

#define ADMUX_REG (*((volatile ADMUX_REG_t *)0x27))


typedef union{
	struct{
		uint8 ADPS_Bits  : 3;
		uint8 ADIE_Bit3  : 1;
		uint8 ADIF_Bit4  : 1;
		uint8 ADATE_Bit5 : 1;
		uint8 ADSC_Bit6  : 1;
		uint8 ADEN_Bit7  : 1;
	};
	uint8 ASCSRA_Register;
}ADCSRA_REG_t;

#define ADCSRA_REG (*((volatile ADCSRA_REG_t *)0x26))

typedef union{
	struct{
		uint8 RESERVED_BITS : 5;
		uint8 ADTS_Bits     : 3;
	};
}SFIOR_REG_ADC_t;

#define SFIOR_REG_ADC (*((volatile SFIOR_REG_ADC_t *)0x50))

//ADC Data Registers
#define ADCH_REG (*((volatile uint8 *)0x25))
#define ADCL_REG (*((volatile uint8 *)0x24))


#define ADC_STILL_FINISHED   1

//The ADC configurations struct that will be used
static struct{
	uint8 ADCStatus                    : 1;
	ADC_Input_Channel_t ADC_CurrentChannel;
	uint8 ADC_ResultAdjustment         : 1;
	VREF_t VREF_Source;
	ADC_Trigger_Source_t Trigger_Source;
	uint8 ADC_INTStatus                : 1;
}ADC_Private_OBJ;

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
