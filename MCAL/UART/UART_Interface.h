/*
 * UART_Interface.h
 *
 *  Created on: Aug 8, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

//External libraries
#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

//Internal libraries
#include "UART_Private.h"

/******************************************Needed enums****************************************/
typedef enum{
	Normal_Async_mode = 0,
	Double_Speed_Async_mode,
	/*Following naming methodology: Sync_Master/Slave_XCKRisingEdgeAction_XCKFallingEdgeAction*/
	Sync_Master_Tx_Rx,
	Sync_Master_Rx_Tx,
	/*<In case of slave synchronous, the max input clock to XCK is fosc/4 (Be below this)>*/
	Sync_Slave_Tx_Rx,
	Sync_Slave_Rx_Tx

}Clock_Generation_Mode_t;

typedef enum{
	Bits_5 = 0,
	Bits_6,
	Bits_7,
	Bits_8,
	Bits_9 = 7
}Data_Bits_Frame_Format_t;

typedef enum{
	None_Parity = 0,
	Even_Parity = 2,
	Odd_Parity
}Parity_Frame_Format_t;

typedef enum{
	Bit_1 = 0,
	Bits_2
}Stop_Bits_Frame_Format_t;

/*****************************************Needed struct**************************************/
/* You must fill the required configurations of the USART in this struct members to be able to
 * initialize the USART or its operation will be totally wrong. Also this struct object will
 * hold the latest updates which you would have done for USART configurations so that you can
 * acquire information about them any time you want without needing to access the AVR registers.
 */
struct{
	uint8 TxINTStatus : 1;
	uint8 RxINTStatus : 1;
	uint8 TxBuffEmptyINTStatus : 1;
	uint32 Copy_SystemClockFreq;
	uint32 BaudRate;
	Clock_Generation_Mode_t Sync_Mode;
	Data_Bits_Frame_Format_t Data_Bits;
	Parity_Frame_Format_t Parity_Check;
	Stop_Bits_Frame_Format_t Stop_Bits;
}UART_Module;

/******************************************Needed macros***************************************/

#define DISABLE       0
#define ENABLE        1


/*<These macros to be used along with the MCAL_USART_ReadUBRRHorUCSRC>*/
#define READ_UCSRC    0
#define READ_UBRRH    1

/*If FE error or PE error is detected in the received data, the read received data will be:*/
#define INVALID_RECEIVED_DATA      0xE404

/***********************************************APIs*******************************************/

Std_ReturnType MCAL_USART_USARTInit();

Std_ReturnType MCAL_USART_USARTTransmitterStatus(uint8 Copy_TxStatus);

Std_ReturnType MCAL_USART_USARTSendData(uint16 Copy_DataToBeSend);

Std_ReturnType MCAL_USART_USARTReceiverStatus(uint8 Copy_RxStatus);

Std_ReturnType MCAL_USART_USARTReceiveData(uint16 *Copy_ReceivedData);

/* To be able to change the Baud Rate, no transmission must be in progress(must be done), and no
 * reception must be in progress and reception is ended and *read its received data as well*.
 * */
Std_ReturnType MCAL_USART_SetBaudRate(const uint32 Copy_SystemClockFreq, const uint32 Copy_BaudRate);

Std_ReturnType MCAL_USART_SetSyncStatusAndFrameFormat(const Clock_Generation_Mode_t Copy_SyncState,
													  const Parity_Frame_Format_t Copy_Parity_Check,
													  const Stop_Bits_Frame_Format_t Copy_Stop_Bits,
													  const Data_Bits_Frame_Format_t Copy_Data_Bits);
Std_ReturnType MCAL_USART_ReadUBRRHorUCSRC(uint8 Copy_RegToBeRead, uint8 *Copy_RegValue);

/*<Interrupts APIs>*/

Std_ReturnType MCAL_USART_USARTTxCompleteINTStatus(uint8 Copy_TxINTStatus);

Std_ReturnType MCAL_USART_SetCallBackTxComplete(void (*Copy_UART_Tx_Complete_Ptr)(void));

Std_ReturnType MCAL_USART_USARTRxCompleteINTStatus(uint8 Copy_RxINTStatus);

Std_ReturnType MCAL_USART_SetCallBackRxComplete(void (*Copy_UART_Rx_Complete_Ptr)(void));

Std_ReturnType MCAL_USART_USARTTxBufferEmptyINTStatus(uint8 Copy_UDRINTStatus);

Std_ReturnType MCAL_USART_SetCallBackTxBufferEmpty(void (*Copy_UART_UDR_Empty_Ptr)(void));

#endif /* MCAL_UART_UART_INTERFACE_H_ */
