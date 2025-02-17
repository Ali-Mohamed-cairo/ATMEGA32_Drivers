/*
 * SPI_Interface.h
 *
 *  Created on: Dec 2, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

#define SPI_DISABLE              0
#define SPI_ENABLE               1

#define SPI_2x_OFF               0
#define SPI_2x_ON                1

#define SPI_INTERRUPT_DISABLE    0
#define SPI_INTERRUPT_ENABLE     1

typedef enum{
	Fosc_Div_4  = 0,
	Fosc_Div_8  = 5,
	Fosc_Div_16 = 1,
	Fosc_Div_32 = 6,
	Fosc_Div_64 = 2,
	Fosc_Div_128
	//If you are disabling SPI fill this parameter in MCAL_SPI_SPIInit API with: NONE
}Clock_Speed_Select_t;

typedef enum{
	Sample_Leading_Edge = 0,
	Sample_Trialing_Edge
	//If you are disabling SPI fill this parameter in MCAL_SPI_SPIInit API with: NONE
}Clock_Phase_t;

typedef enum{
	Rising_Leading_Edge = 0,
	Falling_Leading_Edge
	//If you are disabling SPI fill this parameter in MCAL_SPI_SPIInit API with: NONE
}Clock_Polarity_t;

typedef enum{
	MSB_First = 0,
	LSB_First
	//If you are disabling SPI fill this parameter in MCAL_SPI_SPIInit API with: NONE
}Data_Transmission_Order_t;

typedef enum{
	SPI_Slave = 0,
	SPI_Master
}SPI_Mode_t;

/************************************************APIs*****************************************************/
Std_ReturnType MCAL_SPI_SPIInit(uint8 Copy_SPIStatus, Clock_Speed_Select_t Copy_ClkSpeed, Clock_Phase_t Copy_ClkPhase, Clock_Polarity_t Copy_ClkPolarity, Data_Transmission_Order_t Copy_DataOrder);
Std_ReturnType MCAL_SPI_SPISelectMode(SPI_Mode_t Copy_Mode);

/*<Master_Mode_APIs>*/
Std_ReturnType MCAL_SPI_CreateSlaveToMaster(Pin_Conig_t *Copy_SSPinInfo);
Std_ReturnType MCAL_SPI_MasterActivesSlave(Pin_Conig_t *Copy_Slave);
Std_ReturnType MCAL_SPI_MasterDeactivesSlave(Pin_Conig_t *Copy_Slave);
//This function initiates the transmission when used.
Std_ReturnType MCAL_SPI_Mastersend(uint8 Copy_DataSend);
/*<End of Master_Mode_APIs>*/

/*<Slave_Mode_APIs>*/
Std_ReturnType MCAL_SPI_SlavePrepareDataToBeSendToMaster(uint8 Copy_DataSend);
/*<End of Slave_Mode_APIs>*/

Std_ReturnType MCAL_SPI_ReadReceivedData(uint8 *Copy_RecievedData);

Std_ReturnType MCAL_SPI_GetWriteCollisionFlag(uint8 *Copy_WriteCollisionFlag);
Std_ReturnType MCAL_SPI_DoubleSPISpeedStatus(uint8 Copy_2xStatus);

/*<Interrupt APIs>*/
Std_ReturnType MCAL_SPI_SPIInterruptStatus(uint8 Copy_SPIInterruptStatus);
Std_ReturnType MCAL_SPI_ClearSPIInterruptFlag();
Std_ReturnType MCAL_SPI_SetCallBack(void (*SPI_EOT_SOR_CallBackPtr)(void));//Note:End Of Transmission(EOT) / Start Of Reception(SOR)
#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
