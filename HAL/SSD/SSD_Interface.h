/*
 * SSD_Interface.h
 *
 *  Created on: Nov 6, 2024
 *      Author: Ali Mohamed
 */

#ifndef HAL_SSD_SSD_INTERFACE_H_
#define HAL_SSD_SSD_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

#include "../MCAL/DIO/DIO_Interface.h"

typedef enum{
	MC_Generate_NUM,
	MC_Generate_NUM_AND_CONTROL_ON_OFF
}MC_Control_t;

typedef enum{
	SOFTWARE_DEC,
	HEX_DEC
}Decoder_Type_t;


typedef enum{
	COMMON_CATHODE,
	COMMON_ANODE
}SSD_Type_t;

typedef struct{
	SSD_Type_t SSD_Type;
	Decoder_Type_t Decoder_Type;
	Pin_Conig_t SSD_Common;   //Hex_DEC Common power pin
	Pin_Conig_t SSD_Pin0_A;   //Hex_DEC pin A
	Pin_Conig_t SSD_Pin1_B;   //Hex_DEC pin B
	Pin_Conig_t SSD_Pin2_C;   //Hex_DEC pin C
	Pin_Conig_t SSD_Pin3_D;   //Hex_DEC pin D
	//For the software decoder
	Pin_Conig_t SSD_Pin4_E;   //Hex_DEC pin A
	Pin_Conig_t SSD_Pin5_F;   //Hex_DEC pin B
	Pin_Conig_t SSD_Pin6_G;   //Hex_DEC pin C
	/*  Each time you want a certain value to be displayed on the dedicated it must be
	 * assigned to this variable before sending to any function to display.
	 */
	uint8 ValueToBeDisplayed;
}SSD_Module_t;

Std_ReturnType HAL_SSD_SSDInit(SSD_Module_t *Copy_SSD, MC_Control_t Copy_MC_ControlLevel);

Std_ReturnType HAL_SSD_SSDDisplay(SSD_Module_t *Copy_SSD);

Std_ReturnType HAL_SSD_SSDDisplayNumWithSoftwareDecoder(SSD_Module_t *Copy_SSD);

/*  This function required you to have set the Copy_MC_ControlLevel parameter in the function HAL_SSD_SSDInit when initiating
 * any seven-segment module to be used in it as MC_Generate_NUM_AND_CONTROL_ON_OFF.
 *  This function receives an array of pointers to struct, this pointer is the address of objects of struct of type SSD_Module_t, all these
 *  SSD can be sharing the same pins or the same Hex decoder.
 * */
Std_ReturnType HAL_SSD_SSDArrayDisplay(SSD_Module_t **Copy_SSD, uint8 Copy_NumOfSSD);

#endif /* HAL_SSD_SSD_INTERFACE_H_ */
