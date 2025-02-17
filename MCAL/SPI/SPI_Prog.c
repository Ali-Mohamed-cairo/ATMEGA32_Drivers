/*
 * SPI_Prog.c
 *
 *  Created on: Dec 2, 2024
 *      Author: Ali Mohamed
 */

#include "../MCAL/DIO/DIO_Interface.h"

#include "SPI_Interface.h"
#include "SPI_Config.h"
#include "SPI_Private.h"

static Std_ReturnType MCAL_SPI_SPIWriteData(uint8 Copy_DataSend);
static Std_ReturnType MCAL_SPI_SPIReadData(uint8 *Copy_RecievedData);

//This Pointer is used for the SPI interrupt which occur @ End Of Transmission / Start Of Reception
void (*SPI_EOT_SOR_CallBack)(void) = NULL_PTR;


Std_ReturnType MCAL_SPI_SPIInit(uint8 Copy_SPIStatus, Clock_Speed_Select_t Copy_ClkSpeed, Clock_Phase_t Copy_ClkPhase, Clock_Polarity_t Copy_ClkPolarity, Data_Transmission_Order_t Copy_DataOrder)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if(Copy_SPIStatus == SPI_DISABLE)
	{
		SPCR_REG.SPE_Bit6 = SPI_DISABLE;
	}
	else
	{
		SPCR_REG.SPE_Bit6  = SPI_ENABLE;
		SPCR_REG.CPOL_Bit3 = Copy_ClkPolarity;
		SPCR_REG.CPHA_Bit2 = Copy_ClkPhase;
		SPCR_REG.DORD_Bit5 = Copy_DataOrder;
		if((Copy_ClkSpeed == Fosc_Div_8) || (Copy_ClkSpeed == Fosc_Div_32))
		{
			MCAL_SPI_DoubleSPISpeedStatus(SPI_2x_ON);
		}
		else
		{
			MCAL_SPI_DoubleSPISpeedStatus(SPI_2x_OFF);
		}
		SPCR_REG.SPR_BITs = Copy_ClkSpeed;
	}
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_SPISelectMode(SPI_Mode_t Copy_Mode)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	SPCR_REG.MSTR_Bit4 = Copy_Mode;
	Pin_Conig_t SPI_Pins = {
		 .PORT_ID       = DIO_PORTB
	};
	if(Copy_Mode == SPI_Master)
	{
		SPI_Pins.Pin_Num = SCK_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_OUTPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);

		SPI_Pins.Pin_Num = MOSI_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_OUTPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);

		SPI_Pins.Pin_Num = MISO_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_INPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);

		SPI_Pins.Pin_Num = SS_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_OUTPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);
		MCAL_DIO_SetPinValue(&SPI_Pins, DIO_HIGH);
	}
	else if(Copy_Mode == SPI_Slave)
	{
		SPI_Pins.Pin_Num = SCK_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_INPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);

		SPI_Pins.Pin_Num = MOSI_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_INPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);

		SPI_Pins.Pin_Num = MISO_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_OUTPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);

		SPI_Pins.Pin_Num = SS_PIN;
		SPI_Pins.Pin_Direction = DIO_PIN_INPUT;
		MCAL_DIO_SetPinDirection(&SPI_Pins);
	}
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

/*<Master_Mode_APIs>*/

Std_ReturnType MCAL_SPI_CreateSlaveToMaster(Pin_Conig_t *Copy_SSPinInfo)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Copy_SSPinInfo->Pin_Direction = DIO_PIN_OUTPUT;
	MCAL_DIO_SetPinDirection(Copy_SSPinInfo);
	MCAL_DIO_SetPinValue(Copy_SSPinInfo, DIO_HIGH);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_MasterActivesSlave(Pin_Conig_t *Copy_Slave)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	MCAL_DIO_SetPinValue(Copy_Slave, DIO_LOW);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_MasterDeactivesSlave(Pin_Conig_t *Copy_Slave)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	MCAL_DIO_SetPinValue(Copy_Slave, DIO_HIGH);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
//This function initiates the transmission when used.
Std_ReturnType MCAL_SPI_Mastersend(uint8 Copy_DataSend)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Local_ErrorStatus = MCAL_SPI_SPIWriteData(Copy_DataSend);
	return Local_ErrorStatus;
}

/*<End of Master_Mode_APIs>*/

/*<Slave_Mode_APIs>*/
Std_ReturnType MCAL_SPI_SlavePrepareDataToBeSendToMaster(uint8 Copy_DataSend)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Local_ErrorStatus = MCAL_SPI_SPIWriteData(Copy_DataSend);
	return Local_ErrorStatus;
}
/*<End of Slave_Mode_APIs>*/

Std_ReturnType MCAL_SPI_ReadReceivedData(uint8 *Copy_RecievedData)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	Local_ErrorStatus = MCAL_SPI_SPIReadData(Copy_RecievedData);
	return Local_ErrorStatus;
}

static Std_ReturnType MCAL_SPI_SPIWriteData(uint8 Copy_DataSend)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	SPDR_REG = Copy_DataSend;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
static Std_ReturnType MCAL_SPI_SPIReadData(uint8 *Copy_RecievedData)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_RecievedData = SPDR_REG;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_GetWriteCollisionFlag(uint8 *Copy_WriteCollisionFlag)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	*Copy_WriteCollisionFlag = SPSR_REG.WCOL_Bit6;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_DoubleSPISpeedStatus(uint8 Copy_2xStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	SPSR_REG.SPI2X_Bit0 = Copy_2xStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

/*<Interrupt APIs>*/

Std_ReturnType MCAL_SPI_SPIInterruptStatus(uint8 Copy_SPIInterruptStatus)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	SPCR_REG.SPIE_Bit7 = Copy_SPIInterruptStatus;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_ClearSPIInterruptFlag()
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_SPIStatusREG = SPSR_REG.SPSR_Register;
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}
Std_ReturnType MCAL_SPI_SetCallBack(void (*SPI_EOT_SOR_CallBackPtr)(void))
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	SPI_EOT_SOR_CallBack = SPI_EOT_SOR_CallBackPtr;
	return Local_ErrorStatus;
}

ISR(SPI_STC_vect)
{
	SPI_EOT_SOR_CallBack();
	MCAL_SPI_ClearSPIInterruptFlag();
}
