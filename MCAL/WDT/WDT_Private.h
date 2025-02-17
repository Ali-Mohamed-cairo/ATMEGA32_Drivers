/*
 * WDT_Private.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_WDT_WDT_PRIVATE_H_
#define MCAL_WDT_WDT_PRIVATE_H_

typedef union{
	struct{
		uint8 WDP_BITs      : 3;
		uint8 WDE_Bit3      : 1;
		uint8 WDTOE_Bit4    : 1;
		uint8 RESERVED_BITs : 3;
	};
	uint8 WDTCR_Register;
}WDTCR_REG_t;

#define WDTCR_REG (*((volatile WDTCR_REG_t *)0x41))

#endif /* MCAL_WDT_WDT_PRIVATE_H_ */
