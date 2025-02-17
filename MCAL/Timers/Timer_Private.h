/*
 * Timer_Private.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_TIMERS_TIMER_PRIVATE_H_
#define MCAL_TIMERS_TIMER_PRIVATE_H_

#include "../PLATFORM_TYPES.h"

/********************************************Timer/Counter0***************************************************/

#define TMR0_MAX   255 // (2^8) - 1

#define TCNT0_REG  (*((volatile uint8 *)0x52))

#define OCR0_REG   (*((volatile uint8 *)0x5C))

typedef union{
	struct{
		uint8 CS0_BITs  : 3;
		uint8 WGM01_Bit3: 1;
		uint8 COM0_BITs : 2;
		uint8 WGM00_Bit6: 1;
		uint8 FOC0_Bit7 : 1;
	};
	uint8 TCCR0_Register;
}TCCR0_REG_t;

#define TCCR0_REG  (*((volatile TCCR0_REG_t *)0x53))

/********************************************Timer/Counter1***************************************************/
#define TMR1_MAX    65535 // (2^16) - 1

#define TCNT1_REG   (*((volatile uint16 *)0x4C))

#define OCR1A_REG   (*((volatile uint16 *)0x4A))

#define OCR1B_REG   (*((volatile uint16 *)0x48))

#define ICR1_REG    (*((volatile uint16 *)0x46))

typedef union{
	struct{
		uint8 WGM1_1_0_BITs : 2;
		uint8 FOC1B_Bit2    : 1;
		uint8 FOC1A_Bit3    : 1;
		uint8 COM1B_BITs    : 2;
		uint8 COM1A_BITs    : 2;
	};
	uint8 TCCR1A_Register;
}TCCR1A_REG_t;

#define TCCR1A_REG  (*((volatile TCCR1A_REG_t *)0x4F))

typedef union{
	struct{
		uint8 CS1_BITs      : 3;
		uint8 WGM1_3_2_BITs : 2;
		uint8 RESERVED_Bit5 : 1;
		uint8 ICES1_Bit6    : 1;
		uint8 ICNC1_Bit7    : 1;
	};
	uint8 TCCR1B_Register;
}TCCR1B_REG_t;

#define TCCR1B_REG  (*((volatile TCCR1B_REG_t *)0x4E))
/********************************************Timer/Counter2***************************************************/

/********************************************General Registers for all timers**************************************/

typedef union{
	struct{
		uint8 TOIE0_Bit0  : 1;
		uint8 OCIE0_Bit1  : 1;
		uint8 TOIE1_Bit2  : 1;
		uint8 OCIE1B_Bit3 : 1;
		uint8 OCIE1A_Bit4 : 1;
		uint8 TICIE1_Bit5 : 1;
		uint8 TOIE2_Bit6  : 1;
		uint8 OCIE2_Bit7  : 1;
	};
	uint8 TIMSK_Register;
}TIMSK_REG_t;

#define TIMSK_REG  (*((volatile TIMSK_REG_t *)0x59))

typedef union{
	struct{
		uint8 TOV0_Bit0  : 1;
		uint8 OCF0_Bit1  : 1;
		uint8 TOV1_Bit2  : 1;
		uint8 OCF1B_Bit3 : 1;
		uint8 OCF1A_Bit4 : 1;
		uint8 ICF1_Bit5  : 1;
		uint8 TOV2_Bit6  : 1;
		uint8 OCF2_Bit7  : 1;
	};
	uint8 TIFR_Register;
}TIFR_REG_t;

#define TIFR_REG  (*((volatile TIFR_REG_t *)0x58))

#define TOV0_FLAG 0

#endif /* MCAL_TIMERS_TIMER_PRIVATE_H_ */
