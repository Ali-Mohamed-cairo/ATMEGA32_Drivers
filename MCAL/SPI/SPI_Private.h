/*
 * SPI_Private.h
 *
 *  Created on: Dec 2, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

#include "../PLATFORM_TYPES.h"

#include "../MCAL/DIO/DIO_Interface.h"

#define SPDR_REG    (*((volatile uint8 *)0x2F))

typedef union{
	struct{
		uint8 SPR_BITs  : 2;
		uint8 CPHA_Bit2 : 1;
		uint8 CPOL_Bit3 : 1;
		uint8 MSTR_Bit4 : 1;
		uint8 DORD_Bit5 : 1;
		uint8 SPE_Bit6  : 1;
		uint8 SPIE_Bit7 : 1;
	};
	uint8 SPCR_Register;
}SPCR_REG_t;

#define SPCR_REG  (*((volatile SPCR_REG_t *)0x2D))

typedef union{
	struct{
		uint8 SPI2X_Bit0    : 1;
		uint8 RESERVED_BITs : 5;
		uint8 WCOL_Bit6     : 1;
		uint8 SPIF_Bit7     : 1;
	};
	uint8 SPSR_Register;
}SPSR_REG_t;

#define SPSR_REG  (*((volatile SPSR_REG_t *)0x2E))


#define NONE          0

#define SCK_PIN       DIO_PIN7

#define MISO_PIN      DIO_PIN6

#define MOSI_PIN      DIO_PIN5

#define SS_PIN        DIO_PIN4

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
