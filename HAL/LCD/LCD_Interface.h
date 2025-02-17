/*
 * LCD_Interface.h
 *
 *  Created on: Aug 15, 2024
 *      Author: Ali Mohamed
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

#include "../PLATFORM_TYPES.h"

#include "../MCAL/DIO/DIO_Interface.h"

#define LCD_4_BIT_MODE         0
#define LCD_8_BIT_MODE         1






#define CLCD_LINE_1st             1
#define CLCD_LINE_2nd             2

typedef enum{
	CLCD_1_Line,
	CLCD_2_Line
}Display_Line_Config_t;

typedef enum{
	CLCD_Small_Font,
	CLCD_Large_Font
}Display_Font_t;

typedef enum{
	CLCD_AutoEntireShift_OFF,
	CLCD_AutoEntireShift_ON
}Auto_Entire_Shift_t;

typedef enum{
	CLCD_Auto_Shift_Left,
	CLCD_Auto_Shift_Right
}Auto_Shift_Direction_t;

typedef enum{
	CLCD_Clear_Screen,
	CLCD_Cursor_Home,
	CLCD_Entry_Mode_Set,
	CLCD_Display_On_Off_Control,
	CLCD_Cursor_Or_Display_Shift,
	CLCD_Function_Set,
	CLCD_Set_CGRAM_Address,
	CLCD_Set_DDRAM_Address,  //The first most important and useable command. Also used to set the cursor position.
	CLCD_Read_Busy_Flag_And_Address,
	CLCD_Write_Data_To_Address, //The second most important and useable command.
	CLCD_Read_Data_From_RAM
}CLCD_Command_t;

typedef struct{
	/* SH bit. (0 -> Entire Shifting off) and (1 -> Entire Shifting on).
	 */
	uint8 AutoEntireDisplayShiftControl : 1;

	/* I/D bit. (0 -> Left shift) and (1 -> Right shift)
	 * Automatically affect DDRAM (or CGRAM) address by increment (Right shift[1]) or decrement (Left shift[0])
	 * when it's read/written.
	 */
	uint8 AutoShiftDirection : 1;

	/* B bit. (0 -> Blink off) and (1 -> Blink on).
	 */
	uint8 CursorBlink : 1;

	/*C bit. (0 -> Cursor off) and (1 -> Cursor on).
	 */
	uint8 Cursor_On_Off : 1;

	/*D bit. (0 -> Display off) and (1 -> Display on).
	 */
	uint8 Display_On_Off : 1;

	/* S/C bit and R/L bit. Shifting right/left cursor position or display without writing or reading display data.
	 * 0 -> Shift cursor to left (AC decremented by 1).
	 * 1 -> Shift cursor to right (AC incremented by 1).
	 * 2 -> Shift display to left.
	 * 3 -> Shift display to right.
	 */
	uint8 ShiftPattern : 2;

	/*BF_bit*/
	uint8 CLCD_BusyFlag : 1;

	/*F bit. (0 -> Small font(5*8 dots)) and (1 -> Large font(5*11 dots)).
	 */
	uint8 FontSelector : 1;

	/*N bit. (0 -> One line display mode) and (1 -> Two line display mode).
	 */
	uint8 DisplayLineControl : 1;

	/*DL bit. (0 -> 4-bit data bus mode (DB4:DB7)) and (1 -> 8-bit data bus mode (DB0:DB7))*/
	uint8 CLCD_InterfaceMode : 1;


	uint8 Read_CGRAM_Address : 7;

	uint8 Set_CGRAM_Address;

	    /*DDRAM address*/
	//options: [CLCD_Line_1st, CLCD_Line_2nd]
	uint8 CursorPosition_Row;
	// Options for columns: [0 to 39]
	uint8 CursorPosition_Column;

	//Store the address inside the Address Counter (AC) during the Read busy flag instruction(member for the busy flag present above)
	uint8 AC_Address;

	/*This character will be written in CGRAM or DDRAM depending on the address which is set in the AC(address counter)*/
	uint8 WriteCharacter;


	/*This character will be read from CGRAM or DDRAM depending on the address which is set in the AC(address counter)*/
	uint8 ReadCharacter;
}CLCD_Command_Config_t;

typedef struct{
	uint8 LCD_InterfaceMode:1;
	Display_Line_Config_t NumDisplayLines : 1;
	Display_Font_t FontSize : 1;
	Auto_Entire_Shift_t AutoEntireShift : 1; //Usually off.i.e its value is : CLCD_AutoEntireShift_OFF
	Auto_Shift_Direction_t AutoShiftDirection : 1;
	Pin_Conig_t LCD_E_Pin;
	Pin_Conig_t LCD_RS_Pin;
	Pin_Conig_t LCD_RW_Pin;
	Pin_Conig_t LCD_DB0_Pin;
	Pin_Conig_t LCD_DB1_Pin;
	Pin_Conig_t LCD_DB2_Pin;
	Pin_Conig_t LCD_DB3_Pin;
	Pin_Conig_t LCD_DB4_Pin;
	Pin_Conig_t LCD_DB5_Pin;
	Pin_Conig_t LCD_DB6_Pin;
	Pin_Conig_t LCD_DB7_Pin;
}CLCD_Module_t;

Std_ReturnType HAL_CLCD_Init(CLCD_Module_t *Copy_CLCD);
Std_ReturnType HAL_CLCD_Clear(CLCD_Module_t *Copy_CLCD);
Std_ReturnType HAL_CLCD_CursorHome(CLCD_Module_t *Copy_CLCD);
Std_ReturnType HAL_CLCD_SetCursorPosition(CLCD_Module_t *Copy_CLCD, uint8 Copy_LineNum, uint8 Copy_ColNum);
Std_ReturnType HAL_CLCD_DisplayCharacter(CLCD_Module_t *Copy_CLCD, uint8 Copy_CharacterToBeDisplayed);
Std_ReturnType HAL_CLCD_DisplayDecimalIntegerNumber(CLCD_Module_t *Copy_CLCD, sint32 Copy_NumToBeDisplayed);
Std_ReturnType HAL_CLCD_DisplayString(CLCD_Module_t *Copy_CLCD, uint8 *Copy_StringToBeDisplayed);
Std_ReturnType HAL_CLCD_CreateCommand(CLCD_Command_t Copy_Command_ID, const CLCD_Command_Config_t *Copy_CommandDescrp, uint8 *Copy_CommandValue);
Std_ReturnType HAL_CLCD_SendCommand(CLCD_Module_t *Copy_CLCD, const CLCD_Command_t Copy_Command_ID, CLCD_Command_Config_t *Copy_CommandDescrp, uint8 Copy_CommandValue);
Std_ReturnType HAL_CLCD_ConfigureDataBusDirection(CLCD_Module_t *Copy_CLCD, const uint8 Copy_DataBusDirection);
Std_ReturnType HAL_CLCD_ReadDataBus(CLCD_Module_t *Copy_CLCD, const CLCD_Command_t Copy_Command_ID, CLCD_Command_Config_t *Copy_CommandDescrp);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
