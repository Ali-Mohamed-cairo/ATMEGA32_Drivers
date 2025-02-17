/*
 * UART_Prog.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Ali Mohamed
 */

//External libraries
#include <avr/interrupt.h>
#include "../DIO/DIO_Interface.h"

//Private libraries
#include "UART_Interface.h"
#include "UART_Config.h"

void (*UART_Tx_Complete_Ptr)(void)  = NULL_PTR;

void (*UART_Rx_Complete_Ptr)(void)  = NULL_PTR;

void (*UART_Tx_BuffEmpty_Ptr)(void) = NULL_PTR;

Std_ReturnType MCAL_USART_USARTInit()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Local_ErrorStatus = MCAL_USART_USARTTransmitterStatus(DISABLE);
	Local_ErrorStatus = MCAL_USART_USARTReceiverStatus(DISABLE);
	Local_ErrorStatus = MCAL_USART_SetBaudRate(UART_Module.Copy_SystemClockFreq, UART_Module.BaudRate);
	Local_ErrorStatus = MCAL_USART_SetSyncStatusAndFrameFormat(UART_Module.Sync_Mode, UART_Module.Parity_Check,
										  UART_Module.Stop_Bits, UART_Module.Data_Bits);

	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_USARTTransmitterStatus(uint8 Copy_TxStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UCSRB_REG.TXEN_Bit3 = Copy_TxStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_USART_USARTSendData(uint16 Copy_DataToBeSend)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(UART_Module.Data_Bits == Bits_9)
		UCSRB_REG.TXB8_Bit0 = Copy_DataToBeSend >> 8;
	UDR_REG = Copy_DataToBeSend;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_USART_USARTReceiverStatus(uint8 Copy_RxStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UCSRB_REG.RXEN_Bit4 = Copy_RxStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_USART_USARTReceiveData(uint16 *Copy_ReceivedData)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_ReceivedData = 0;
	if(UCSRA_REG.FE_Bit4 | UCSRA_REG.PE_Bit2)//Handling the Frame Error and the Parity Error cases.
	{
		*Copy_ReceivedData = UDR_REG;
		*Copy_ReceivedData = INVALID_RECEIVED_DATA;
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		while(UCSRA_REG.RXC_Bit7 == USART_STILL_RECIEVE);
		if(UART_Module.Data_Bits == Bits_9)
			*Copy_ReceivedData = UCSRB_REG.RXB8_Bit1;
		*Copy_ReceivedData = (*Copy_ReceivedData << 8) | UDR_REG;
		Local_ErrorStatus = E_OK;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_USART_SetBaudRate(const uint32 Copy_SystemClockFreq, const uint32 Copy_BaudRate)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint16 Local_UBRRValue = 0;
	if(((UCSRB_REG.TXEN_Bit3) & (~(UCSRA_REG.UDRE_Bit5))) /*Transmission in progress*/
	   || ((UCSRB_REG.RXEN_Bit4) & (UCSRA_REG.RXC_Bit7))) /*Reception in progress or done but not read*/
	{
		Local_ErrorStatus = E_NOT_OK;
	}
	else
	{
		switch(UART_Module.Sync_Mode)
		{
		case Normal_Async_mode:
			Local_UBRRValue =(Copy_SystemClockFreq / (16 * Copy_BaudRate)) - 1;
			UBRRL_REG = Local_UBRRValue;
			UBRRH_REG = (((uint16)Local_UBRRValue) >> 8) & (0b00001111);
			UART_Module.BaudRate = Copy_BaudRate;
			Local_ErrorStatus = E_OK;
			break;
		case Double_Speed_Async_mode:
			Local_UBRRValue =(Copy_SystemClockFreq / (8 * Copy_BaudRate)) - 1;
			UBRRL_REG = Local_UBRRValue;
			UBRRH_REG = (((uint16)Local_UBRRValue) >> 8) & (0b00001111);
			UART_Module.BaudRate = Copy_BaudRate;
			Local_ErrorStatus = E_OK;
			break;
		case Sync_Master_Tx_Rx:
		case Sync_Master_Rx_Tx:
			Local_UBRRValue =(Copy_SystemClockFreq / (2 * Copy_BaudRate)) - 1;
			UBRRL_REG = Local_UBRRValue;
			UBRRH_REG = (((uint16)Local_UBRRValue) >> 8) & (0b00001111);
			UART_Module.BaudRate = Copy_BaudRate;
			Local_ErrorStatus = E_OK;
			break;
		default:
			Local_ErrorStatus = E_NOT_OK;
			break;
		}
	}
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_SetSyncStatusAndFrameFormat(const Clock_Generation_Mode_t Copy_SyncStatus,
													  const Parity_Frame_Format_t Copy_Parity_Check,
													  const Stop_Bits_Frame_Format_t Copy_Stop_Bits,
													  const Data_Bits_Frame_Format_t Copy_Data_Bits)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UCSRC_REG_t Local_UCSRCValue;
	//Choose to write in UCSRC not UBRRH.
	Local_UCSRCValue.URSEL_Bit7 = SET;
	/* Since we will write in UCSRA during setting the synchronization modes, it's recommended
	* from the data-sheet to write the bits: FE, DOR, and PE in UCSRA by zero when writing in USCRA.
	*/
	UCSRA_REG.FE_Bit4  = CLEAR;
	UCSRA_REG.DOR_Bit3 = CLEAR;
	UCSRA_REG.PE_Bit2  = CLEAR;
	//Set the Synchronization mode settings
	if((Copy_SyncStatus == Normal_Async_mode) || (Copy_SyncStatus == Double_Speed_Async_mode))
	{
		Local_UCSRCValue.UMSEL_Bit6 = CLEAR;
		Local_UCSRCValue.UCPOL_Bit0 = CLEAR;
		if(Copy_SyncStatus == Normal_Async_mode)
			UCSRA_REG.U2X_Bit1 = CLEAR;
		else
			UCSRA_REG.U2X_Bit1 = SET;
		UART_Module.Sync_Mode = Copy_SyncStatus;
		Local_ErrorStatus = E_OK;
	}
	else if((Copy_SyncStatus == Sync_Master_Tx_Rx) || (Copy_SyncStatus == Sync_Master_Rx_Tx) ||
			(Copy_SyncStatus == Sync_Slave_Tx_Rx) || (Copy_SyncStatus == Sync_Slave_Rx_Tx))
	{
		Local_UCSRCValue.UMSEL_Bit6 = SET;
		UCSRA_REG.U2X_Bit1 = CLEAR;
		if((Copy_SyncStatus == Sync_Master_Tx_Rx) || (Copy_SyncStatus == Sync_Master_Rx_Tx))
		{
			Pin_Conig_t Local_XCKPin = {
					.PORT_ID = DIO_PORTB,
					.Pin_Num = DIO_PIN0,
					.Pin_Direction = DIO_PIN_OUTPUT
			};
			Local_ErrorStatus = MCAL_DIO_SetPinDirection(&Local_XCKPin);
			if(Copy_SyncStatus == Sync_Master_Tx_Rx)
				Local_UCSRCValue.UCPOL_Bit0 = CLEAR;
			else
				Local_UCSRCValue.UCPOL_Bit0 = SET;
		}
		else
		{
			Pin_Conig_t Local_XCKPin = {
					.PORT_ID = DIO_PORTB,
					.Pin_Num = DIO_PIN0,
					.Pin_Direction = DIO_PIN_INPUT
			};
			Local_ErrorStatus = MCAL_DIO_SetPinDirection(&Local_XCKPin);
			if(Copy_SyncStatus == Sync_Slave_Tx_Rx)
				Local_UCSRCValue.UCPOL_Bit0 = CLEAR;
			else
				Local_UCSRCValue.UCPOL_Bit0 = SET;
		}
		UART_Module.Sync_Mode = Copy_SyncStatus;
	}
	else
		Local_ErrorStatus = E_NOT_OK;
	//Set the parity check mode
	Local_UCSRCValue.UPM_BITs = Copy_Parity_Check;
	//Set the stop bits number
	Local_UCSRCValue.USBS_Bit3 = Copy_Stop_Bits;
	//Set the data(character) bits number in a frame.
	Local_UCSRCValue.UCSZ_1_0_BITs = Copy_Data_Bits;
	UCSRB_REG.UCSZ2_Bit2 = ((uint8)Copy_Data_Bits) >> 2; //In case of 9-bits data, the UCSZ2 bit UCSRB must be set, otherwise it's cleared
	//Assign the UCSRC value to it.
	UCSRC_REG = Local_UCSRCValue.UCSRC_Register;
	Local_ErrorStatus = Local_ErrorStatus && E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_USART_ReadUBRRHorUCSRC(uint8 Copy_RegToBeRead, uint8 *Copy_RegValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_RegValue = UBRRH_REG;
	if(Copy_RegToBeRead == READ_UCSRC)
		*Copy_RegValue = UCSRC_REG;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_USARTTxCompleteINTStatus(uint8 Copy_TxINTStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UCSRB_REG.TXCIE_Bit6 = Copy_TxINTStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_SetCallBackTxComplete(void (*Copy_UART_Tx_Complete_Ptr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UART_Tx_Complete_Ptr = Copy_UART_Tx_Complete_Ptr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_USARTRxCompleteINTStatus(uint8 Copy_RxINTStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UCSRB_REG.RXCIE_Bit7 = Copy_RxINTStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_SetCallBackRxComplete(void (*Copy_UART_Rx_Complete_Ptr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UART_Rx_Complete_Ptr = Copy_UART_Rx_Complete_Ptr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_USARTTxBufferEmptyINTStatus(uint8 Copy_UDRINTStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UCSRB_REG.UDRIE_Bit5 = Copy_UDRINTStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType MCAL_USART_SetCallBackTxBufferEmpty(void (*Copy_UART_UDR_Empty_Ptr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	UART_Tx_BuffEmpty_Ptr = Copy_UART_UDR_Empty_Ptr;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

ISR(USART_TXC_vect)
{
	UART_Tx_Complete_Ptr();
	/* Clear the TXC bit after executing the ISR by writing one to its location, although this can
	* be done automatically by hardware.
	*/
	UCSRA_REG.TXC_Bit6 = SET;
}

ISR(USART_RXC_vect)
{
	UART_Rx_Complete_Ptr();
}

ISR(USART_UDRE_vect)
{
	UART_Tx_BuffEmpty_Ptr();
}

