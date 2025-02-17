/*
 * UART_Private.h
 *
 *  Created on: Aug 8, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

//External libraries
#include "../PLATFORM_TYPES.h"


#define UDR_REG        (*((volatile uint8 *)0x2C))

typedef union{
	struct{
		uint8 MPCM_Bit0 : 1;
		uint8 U2X_Bit1  : 1;
		uint8 PE_Bit2   : 1;
		uint8 DOR_Bit3  : 1;
		uint8 FE_Bit4   : 1;
		uint8 UDRE_Bit5 : 1;
		uint8 TXC_Bit6  : 1;
		uint8 RXC_Bit7  : 1;
	};
	uint8 UCSRA_Register;
}UCSRA_REG_t;

#define UCSRA_REG  (*((volatile UCSRA_REG_t *)0x2B))

typedef union{
	struct{
		uint8 TXB8_Bit0  : 1;
		uint8 RXB8_Bit1  : 1;
		uint8 UCSZ2_Bit2 : 1;
		uint8 TXEN_Bit3  : 1;
		uint8 RXEN_Bit4  : 1;
		uint8 UDRIE_Bit5 : 1;
		uint8 TXCIE_Bit6 : 1;
		uint8 RXCIE_Bit7 : 1;
	};
	uint8 UCSRB_Register;
}UCSRB_REG_t;

#define UCSRB_REG  (*((volatile UCSRB_REG_t *)0x2A))

#define UBRRH_REG  (*((volatile uint8 *)0x40))

typedef union{
	struct{
		uint8 UCPOL_Bit0    : 1;
		uint8 UCSZ_1_0_BITs : 2;
		uint8 USBS_Bit3     : 1;
		uint8 UPM_BITs      : 2;
		uint8 UMSEL_Bit6    : 1;
		uint8 URSEL_Bit7    : 1;
	};
	uint8 UCSRC_Register;
}UCSRC_REG_t;

#define UCSRC_REG  (*((volatile uint8 *)0x40))

#define UBRRL_REG  (*((volatile uint8 *)0x29))


#define USART_STILL_RECIEVE      0

#endif /* MCAL_UART_UART_PRIVATE_H_ */
