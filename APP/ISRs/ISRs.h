/*
 * ISRs.h
 *
 *  Created on: Jul 9, 2024
 *      Author: Ali Mohamed
 */

#ifndef APP_ISRS_ISRS_H_
#define APP_ISRS_ISRS_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

#include "../MCAL/UART/UART_Interface.h"

void APP_EXTINT0_ISR(void);

void APP_EXTINT1_ISR(void);

void APP_EXTINT2_ISR(void);

void APP_ADCINT_ISR(void);

void APP_USARTRxComplete_ISR(void);

void APP_USARTTxComplete_ISR(void);

void APP_USARTTxBuffEmpty_ISR(void);

void APP_TMR0Overflow_ISR(void);

void APP_TMR0CompareMatch_ISR(void);

void APP_TMR1Overflow_ISR(void);

void APP_TMR1CompareMatchChannel_A_ISR(void);

void APP_TMR1CompareMatchChannel_B_ISR(void);

void APP_TMR1CompareMatchChannel_IC_ISR(void);

//This ISR is used for the SPI interrupt which occur @ End Of Transmission / Start Of Reception
void APP_SPI_EOT_SOR_ISR(void);

#endif /* APP_ISRS_ISRS_H_ */
