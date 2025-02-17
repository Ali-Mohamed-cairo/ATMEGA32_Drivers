/*
 * ISRs.c
 *
 *  Created on: Jul 9, 2024
 *      Author: Ali Mohamed
 */

#include "ISRs.h"

void APP_EXTINT0_ISR(void)
{
	//Write here the handling routine
}


void APP_EXTINT1_ISR(void)
{
	//Write here the handling routine
}


void APP_EXTINT2_ISR(void)
{
	//Write here the handling routine
}


void APP_ADCINT_ISR(void)
{
	//Write here the handling routine
}


void APP_USARTRxComplete_ISR(void)
{
	uint16 Local_ReceivedData = 0;
	/* Inside the routine you must read the UDR to pick the received data and consequently clear
	* the RXC flag preventing any re-interrupt once the ISR is executed.
	*/
	MCAL_USART_USARTReceiveData(&Local_ReceivedData);
	//Write here the handling routine
}

void APP_USARTTxComplete_ISR(void)
{
	//Write here the handling routine
}

void APP_USARTTxBuffEmpty_ISR(void)
{
	/* When this interrupt is used, the ISR must either write new data to transmitter buffer
	*  in order to clear UDRE flag or disable the Tx Buffer Empty Interrupt, otherwise a new
	*  interrupt will occur once the interrupt routine terminates.
	*/
	/* Write new data to transmitter buffer:
	 * MCAL_USART_USARTSendData(_Write_Data_Here_);
	 * */
	/* Disable the Tx Buffer Empty Interrupt:
	 * MCAL_USART_USARTTxBufferEmptyINTStatus(DISABLE);
	 * */
}


void APP_TMR0Overflow_ISR(void)
{
	//Write here the handling routine
}

void APP_TMR0CompareMatch_ISR(void)
{
	//Write here the handling routine
}


void APP_TMR1Overflow_ISR(void)
{
	//Write here the handling routine
}

void APP_TMR1CompareMatchChannel_A_ISR(void)
{
	//Write here the handling routine
}

void APP_TMR1CompareMatchChannel_B_ISR(void)
{
	//Write here the handling routine
}

void APP_TMR1CompareMatchChannel_IC_ISR(void)
{
	//Write here the handling routine
}


//This ISR is used for the SPI interrupt which occur @ End Of Transmission / Start Of Reception
void APP_SPI_EOT_SOR_ISR(void)
{
	//Write here the handling routine
}
