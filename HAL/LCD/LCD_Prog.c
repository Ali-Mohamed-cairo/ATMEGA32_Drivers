/*
 * LCD_Prog.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Ali Mohamed
 */

#include <util/delay.h>

#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "LCD_Private.h"

Std_ReturnType HAL_CLCD_Init(CLCD_Module_t *Copy_CLCD)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;

	CLCD_Command_Config_t Local_CLCD_ConfigurationsVar;
	uint8 Local_CLCD_ConfigurationsCommands;

	Local_CLCD_ConfigurationsVar.CLCD_InterfaceMode = (*Copy_CLCD).LCD_InterfaceMode;
	Local_CLCD_ConfigurationsVar.DisplayLineControl = (*Copy_CLCD).NumDisplayLines;
	Local_CLCD_ConfigurationsVar.FontSelector = (*Copy_CLCD).FontSize;
	Local_CLCD_ConfigurationsVar.AutoEntireDisplayShiftControl = (*Copy_CLCD).AutoEntireShift;
	Local_CLCD_ConfigurationsVar.AutoShiftDirection = (*Copy_CLCD).AutoShiftDirection;

	Local_CLCD_ConfigurationsVar.Display_On_Off = 1;
	Local_CLCD_ConfigurationsVar.Cursor_On_Off = 1;
	Local_CLCD_ConfigurationsVar.CursorBlink = 1;

	(*Copy_CLCD).LCD_E_Pin.Pin_Direction = DIO_PIN_OUTPUT;
	(*Copy_CLCD).LCD_RS_Pin.Pin_Direction = DIO_PIN_OUTPUT;
	(*Copy_CLCD).LCD_RW_Pin.Pin_Direction = DIO_PIN_OUTPUT;

	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_E_Pin));
	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_RS_Pin));
	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_RW_Pin));

	//Recommended delay from internet
	_delay_ms(20);

	if((*Copy_CLCD).LCD_InterfaceMode == LCD_4_BIT_MODE)
	{
		/*Initiation constant command sequence. In these cases, the Local_CLCD_ConfigurationsVar is useless*/
		HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Function_Set, &Local_CLCD_ConfigurationsVar, INITIAL_CLCD_FS_4_BIT_COMMAND_1);
		HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Function_Set, &Local_CLCD_ConfigurationsVar, INITIAL_CLCD_FS_4_BIT_COMMAND_2);
	}

	//Set the CLCD to the required interfacing mode(8-bit or 4-bit), font size, and number of display lines.
	HAL_CLCD_CreateCommand(CLCD_Function_Set, &Local_CLCD_ConfigurationsVar, &Local_CLCD_ConfigurationsCommands);
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Function_Set, &Local_CLCD_ConfigurationsVar, Local_CLCD_ConfigurationsCommands);

	HAL_CLCD_CreateCommand(CLCD_Display_On_Off_Control, &Local_CLCD_ConfigurationsVar, &Local_CLCD_ConfigurationsCommands);
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Display_On_Off_Control, &Local_CLCD_ConfigurationsVar, Local_CLCD_ConfigurationsCommands);

	HAL_CLCD_CreateCommand(CLCD_Entry_Mode_Set, &Local_CLCD_ConfigurationsVar, &Local_CLCD_ConfigurationsCommands);
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Entry_Mode_Set, &Local_CLCD_ConfigurationsVar, Local_CLCD_ConfigurationsCommands);

	HAL_CLCD_CursorHome(Copy_CLCD);

	HAL_CLCD_Clear(Copy_CLCD);

	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_Clear(CLCD_Module_t *Copy_CLCD)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	//Declaring an arbitirary unuseful/unused variable of data type CLCD_Command_Config_t for the HAL_CLCD_SendCommand call statement
	CLCD_Command_Config_t Local_UnusefulVar;
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Clear_Screen, &Local_UnusefulVar, CLCD_CLEAR);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_CursorHome(CLCD_Module_t *Copy_CLCD)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	//Declaring an arbitirary unuseful/unused variable of data type CLCD_Command_Config_t for the HAL_CLCD_SendCommand call statement
	CLCD_Command_Config_t Local_UnusefulVar;
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Cursor_Home, &Local_UnusefulVar, CLCD_CURSOR_HOME);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_SetCursorPosition(CLCD_Module_t *Copy_CLCD, uint8 Copy_LineNum, uint8 Copy_ColNum)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	CLCD_Command_Config_t Local_CLCD_PositionCommandConfiguration;
	uint8 Local_PositionCommand = 0;
	Local_CLCD_PositionCommandConfiguration.CursorPosition_Row = Copy_LineNum;
	Local_CLCD_PositionCommandConfiguration.CursorPosition_Column = Copy_ColNum;
	HAL_CLCD_CreateCommand(CLCD_Set_DDRAM_Address, &Local_CLCD_PositionCommandConfiguration, &Local_PositionCommand);
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Set_DDRAM_Address, &Local_CLCD_PositionCommandConfiguration, Local_PositionCommand);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_DisplayCharacter(CLCD_Module_t *Copy_CLCD, uint8 Copy_CharacterToBeDisplayed)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	CLCD_Command_Config_t Local_CLCD_DisplayCommandConfiguration;
	uint8 Local_WriteCommand = 0;
	Local_CLCD_DisplayCommandConfiguration.WriteCharacter = Copy_CharacterToBeDisplayed;
	HAL_CLCD_CreateCommand(CLCD_Write_Data_To_Address, &Local_CLCD_DisplayCommandConfiguration, &Local_WriteCommand);
	HAL_CLCD_SendCommand(Copy_CLCD, CLCD_Write_Data_To_Address, &Local_CLCD_DisplayCommandConfiguration, Local_WriteCommand);
	Local_ErrorStatus = E_OK;
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_DisplayDecimalIntegerNumber(CLCD_Module_t *Copy_CLCD, sint32 Copy_NumToBeDisplayed)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_CurrentDigit = 0;
	if(Copy_NumToBeDisplayed < 0)
	{
		HAL_CLCD_DisplayCharacter(Copy_CLCD, '-');
		Copy_NumToBeDisplayed = Copy_NumToBeDisplayed * -1;
	}
	do{
		Local_CurrentDigit = Copy_NumToBeDisplayed % 10;
		Copy_NumToBeDisplayed /= 10;
		HAL_CLCD_DisplayCharacter(Copy_CLCD, Local_CurrentDigit + ASCII_OF_ZERO);
	}while(Copy_NumToBeDisplayed != 0);

	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_DisplayString(CLCD_Module_t *Copy_CLCD, uint8 *Copy_StringToBeDisplayed)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	while((*Copy_StringToBeDisplayed) != '\0')
	{
		HAL_CLCD_DisplayCharacter(Copy_CLCD, *Copy_StringToBeDisplayed);
		++Copy_StringToBeDisplayed;
	}
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_CreateCommand(CLCD_Command_t Copy_Command_ID, const CLCD_Command_Config_t *Copy_CommandDescrp, uint8 *Copy_CommandValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	switch(Copy_Command_ID)
	{
	case CLCD_Entry_Mode_Set:
		*Copy_CommandValue = EM_FIXED_VALUE + ((*Copy_CommandDescrp).AutoEntireDisplayShiftControl << S_BIT) + ((*Copy_CommandDescrp).AutoShiftDirection << ID_BIT);
		Local_ErrorStatus = E_OK;
		break;
	case CLCD_Display_On_Off_Control:
		*Copy_CommandValue = DC_FIXED_VALUE + ((*Copy_CommandDescrp).Display_On_Off << D_BIT) + ((*Copy_CommandDescrp).Cursor_On_Off << C_BIT) + ((*Copy_CommandDescrp).CursorBlink << B_BIT);
		Local_ErrorStatus = E_OK;
		break;
	case CLCD_Cursor_Or_Display_Shift:
		*Copy_CommandValue = CDS_FIXED_VALUE + ((*Copy_CommandDescrp).ShiftPattern << RL_BIT);
		Local_ErrorStatus = E_OK;
		break;
	case CLCD_Function_Set:
		*Copy_CommandValue = FS_FIXED_VALUE + ((*Copy_CommandDescrp).CLCD_InterfaceMode << DL_BIT) + ((*Copy_CommandDescrp).DisplayLineControl << N_BIT) + ((*Copy_CommandDescrp).FontSelector << F_BIT);
		Local_ErrorStatus = E_OK;
		break;
	case CLCD_Set_CGRAM_Address:
		if((*Copy_CommandDescrp).Set_CGRAM_Address <= MAX_CGRAM_ADDRESS)
		{
			*Copy_CommandValue = S_CGRAM_FIXED_VALUE + (*Copy_CommandDescrp).Set_CGRAM_Address;
			Local_ErrorStatus = E_OK;
		}
		else
		{
			Local_ErrorStatus = E_NOT_OK;
		}
		break;
	case CLCD_Set_DDRAM_Address:
		if((*Copy_CommandDescrp).CursorPosition_Row == CLCD_LINE_1st)
		{
			*Copy_CommandValue = S_DDRAM_FIXED_VALUE + CLCD_LINE_FIRST_ADDRESS + (*Copy_CommandDescrp).CursorPosition_Column;
			Local_ErrorStatus = E_OK;
		}
		else if((*Copy_CommandDescrp).CursorPosition_Row == CLCD_LINE_2nd)
		{
			*Copy_CommandValue = S_DDRAM_FIXED_VALUE + CLCD_LINE_SECOND_ADDRESS + (*Copy_CommandDescrp).CursorPosition_Column;
			Local_ErrorStatus = E_OK;
		}
		break;
	case CLCD_Write_Data_To_Address:
        *Copy_CommandValue = (*Copy_CommandDescrp).WriteCharacter;
        Local_ErrorStatus = E_OK;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		break;
	}

	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_SendCommand(CLCD_Module_t *Copy_CLCD, const CLCD_Command_t Copy_Command_ID, CLCD_Command_Config_t *Copy_CommandDescrp, uint8 Copy_CommandValue)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_PinNum = 0;
	uint8 Local_SendCycles = 2;

	switch(Copy_Command_ID)
	{
	case CLCD_Clear_Screen:
	case CLCD_Cursor_Home:
	case CLCD_Entry_Mode_Set:
	case CLCD_Display_On_Off_Control:
	case CLCD_Cursor_Or_Display_Shift:
	case CLCD_Function_Set:
	case CLCD_Set_DDRAM_Address:
	case CLCD_Set_CGRAM_Address:
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RS_Pin), DIO_LOW);
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RW_Pin), DIO_LOW);
		Local_ErrorStatus = E_OK;
		break;
	case CLCD_Read_Busy_Flag_And_Address:
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RS_Pin), DIO_LOW);
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RW_Pin), DIO_HIGH);
		//Call the function HAL_CLCD_ReadDataBus which is made for this command essentially
		HAL_CLCD_ReadDataBus(Copy_CLCD, Copy_Command_ID, Copy_CommandDescrp);
		Local_ErrorStatus = E_OK;
		return Local_ErrorStatus;
		break;
	case CLCD_Write_Data_To_Address:
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RS_Pin), DIO_HIGH);
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RW_Pin), DIO_LOW);
		Local_ErrorStatus = E_OK;
		break;
	case CLCD_Read_Data_From_RAM:
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RS_Pin), DIO_HIGH);
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_RW_Pin), DIO_HIGH);
		//Call the function HAL_CLCD_ReadDataBus which is made for this command essentially
		HAL_CLCD_ReadDataBus(Copy_CLCD, Copy_Command_ID, Copy_CommandDescrp);
		Local_ErrorStatus = E_OK;
		return Local_ErrorStatus;
		break;
	default:
		Local_ErrorStatus = E_NOT_OK;
		return Local_ErrorStatus;
		break;
	}

	HAL_CLCD_ConfigureDataBusDirection(Copy_CLCD, LCD_DATA_BUS_OUTPUT);

	if((*Copy_CLCD).LCD_InterfaceMode == LCD_8_BIT_MODE)
	{
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB0_Pin), GET_BIT(Copy_CommandValue, Local_PinNum));
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB1_Pin), GET_BIT(Copy_CommandValue, (Local_PinNum + 1)));
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB2_Pin), GET_BIT(Copy_CommandValue, (Local_PinNum + 2)));
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB3_Pin), GET_BIT(Copy_CommandValue, (Local_PinNum + 3)));
		Local_SendCycles--;
	}

	Local_PinNum = HIGH_NIBBLE_START;

	do{
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB4_Pin), GET_BIT(Copy_CommandValue, Local_PinNum));
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB5_Pin), GET_BIT(Copy_CommandValue, (Local_PinNum + 1)));
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB6_Pin), GET_BIT(Copy_CommandValue, (Local_PinNum + 2)));
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_DB7_Pin), GET_BIT(Copy_CommandValue, (Local_PinNum + 3)));

		Local_SendCycles--;
		Local_PinNum = 0;

		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_E_Pin), DIO_HIGH);
		_delay_ms(1);
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_E_Pin), DIO_LOW);
		_delay_ms(5); //Delay from me (Not recommended from the datasheet)

	}while(Local_SendCycles > 0);

	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_ConfigureDataBusDirection(CLCD_Module_t *Copy_CLCD, const uint8 Copy_DataBusDirection)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	if((*Copy_CLCD).LCD_InterfaceMode == LCD_8_BIT_MODE)
	{
		(*Copy_CLCD).LCD_DB0_Pin.Pin_Direction = Copy_DataBusDirection;
		(*Copy_CLCD).LCD_DB1_Pin.Pin_Direction = Copy_DataBusDirection;
		(*Copy_CLCD).LCD_DB2_Pin.Pin_Direction = Copy_DataBusDirection;
		(*Copy_CLCD).LCD_DB3_Pin.Pin_Direction = Copy_DataBusDirection;

		MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB0_Pin));
		MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB1_Pin));
		MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB2_Pin));
		MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB3_Pin));
	}

	(*Copy_CLCD).LCD_DB4_Pin.Pin_Direction = Copy_DataBusDirection;
	(*Copy_CLCD).LCD_DB5_Pin.Pin_Direction = Copy_DataBusDirection;
	(*Copy_CLCD).LCD_DB6_Pin.Pin_Direction = Copy_DataBusDirection;
	(*Copy_CLCD).LCD_DB7_Pin.Pin_Direction = Copy_DataBusDirection;

	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB4_Pin));
	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB5_Pin));
	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB6_Pin));
	MCAL_DIO_SetPinDirection(&((*Copy_CLCD).LCD_DB7_Pin));
	return Local_ErrorStatus;
}

Std_ReturnType HAL_CLCD_ReadDataBus(CLCD_Module_t *Copy_CLCD, const CLCD_Command_t Copy_Command_ID, CLCD_Command_Config_t *Copy_CommandDescrp)
{
	Std_ReturnType Local_ErrorStatus = E_NOT_OK;
	uint8 Local_PinNum = 0;
	uint8 Local_ReadCycles = 2;
	DIO_PIN_VALUE_t CLCD_PinValues = 0;
	uint8 Local_DataBusValue = 0;

	//Configure the data bus as input pins
	HAL_CLCD_ConfigureDataBusDirection(Copy_CLCD, LCD_DATA_BUS_INPUT);

	//Alert the CLCD to perform the required instruction
	MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_E_Pin), DIO_HIGH);
	_delay_ms(1);
	MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_E_Pin), DIO_LOW);
	_delay_ms(5); //Delay from me (Not recommended from the datasheet)

	if((*Copy_CLCD).LCD_InterfaceMode == LCD_8_BIT_MODE)
	{
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB0_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << Local_PinNum);
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB1_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << (++Local_PinNum));
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB2_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << (++Local_PinNum));
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB3_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << (++Local_PinNum));
		Local_ReadCycles--;
	}
	Local_PinNum = HIGH_NIBBLE_START;

	do{
		//Read the Data bus pins common between the two reading commands available for CLCD
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB4_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << Local_PinNum);
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB5_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << (++Local_PinNum));
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB6_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << (++Local_PinNum));
		MCAL_DIO_ReadPinValue(&((*Copy_CLCD).LCD_DB7_Pin), &CLCD_PinValues);
		Local_DataBusValue |= (CLCD_PinValues << (++Local_PinNum));

		Local_ReadCycles--;
		Local_PinNum = 0;

		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_E_Pin), DIO_HIGH);
		_delay_ms(1);
		MCAL_DIO_SetPinValue(&((*Copy_CLCD).LCD_E_Pin), DIO_LOW);
		_delay_ms(5); //Delay from me (Not recommended from the datasheet)

	}while(Local_ReadCycles > 0);


	if(Copy_Command_ID == CLCD_Read_Busy_Flag_And_Address)
	{
		//Read busy flag
		(*Copy_CommandDescrp).CLCD_BusyFlag = GET_BIT(Local_DataBusValue, 7);
		//Assign the data bus value to the AC_address variable
		(*Copy_CommandDescrp).AC_Address = (Local_DataBusValue & CLCD_READING_AC_ADDRESS_MASK);
		Local_ErrorStatus = E_OK;
	}
	else if(Copy_Command_ID == CLCD_Read_Data_From_RAM)
	{
		//Assign the data bus value to the AC_address variable
		(*Copy_CommandDescrp).ReadCharacter = Local_DataBusValue;
		Local_ErrorStatus = E_OK;
	}

	return Local_ErrorStatus;
}
