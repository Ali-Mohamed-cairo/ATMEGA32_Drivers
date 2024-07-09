/* 
 * File:   EXT_Interrupt_Private.h
 * Author: Ali Mohamed
 *
 * Created on March 6, 2024, 12:48 PM
 */

#ifndef EXT_INTERRUPT_PRIVATE_H
#define	EXT_INTERRUPT_PRIVATE_H

typedef union{
	struct{
		uint8 ISC0_BITs     : 2;
		uint8 ISC1_BITs     : 2;
		uint8 RESERVED_BITs : 4;
	};
	uint8 MCUCR_Register;
}MCUCR_REG_t;

#define MCUCR_REG  (*((volatile MCUCR_REG_t *)0x55))

typedef union{
	struct{
		uint8 RESERVED_BITs_6 : 6;
		uint8 ISC2_BIT6       : 1;
		uint8 RESERVED_BIT7   : 1;
	};
	uint8 MCUCSR_Register;
}MCUCSR_REG_t;

#define MCUCSR_REG  (*((volatile MCUCSR_REG_t *)0x54))

#define GICR_REG    (*((volatile uint8 *)0x5B))

#define GIFR_REG    (*((volatile uint8 *)0x5A))

#endif	/* EXT_INTERRUPT_PRIVATE_H */

