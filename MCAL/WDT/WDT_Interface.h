/*
 * WDT_Interface.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_WDT_WDT_INTERFACE_H_
#define MCAL_WDT_WDT_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

#define WDT_DISABLE    0
#define WDT_ENABLE     1

typedef enum{
	TO_17_ms = 0,
	TO_34_ms,
	TO_68_ms,
	TO_140_ms,
	TO_270_ms,
	TO_550_ms,
	TO_1100_ms,
	TO_2200_ms
}WDT_Time_Out_VCC_3_t;

typedef enum{
	TO_16_ms = 0,
	TO_32_ms,
	TO_65_ms,
	TO_130_ms,
	TO_260_ms,
	TO_520_ms,
	TO_1000_ms,
	TO_2100_ms
}WDT_Time_Out_VCC_5_t;

Std_ReturnType MCAL_WDT_WDTStatus(uint8 Copy_WDTStatus);

Std_ReturnType MCAL_WDT_TimeOutSelect(uint8 Copy_TimeOut); // Choose Copy_TimeOut either from: WDT_Time_Out_VCC_3_t or WDT_Time_Out_VCC_5_t

#endif /* MCAL_WDT_WDT_INTERFACE_H_ */
