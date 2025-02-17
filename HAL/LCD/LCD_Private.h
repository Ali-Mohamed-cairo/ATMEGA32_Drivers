/*
 * LCD_Private.h
 *
 *  Created on: Oct 13, 2024
 *      Author: Ali Mohamed
 */

#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_

#define INITIAL_CLCD_FS_8_BIT_COMMAND     0x38

#define INITIAL_CLCD_FS_4_BIT_COMMAND_1   0x33
#define INITIAL_CLCD_FS_4_BIT_COMMAND_2   0x32

/*CLCD_Entry_Mode_Set variable bits location*/
#define EM_FIXED_VALUE     0x04
#define S_BIT                 0
#define ID_BIT                1

/*CLCD_Display_On_Off_Control variable bits location*/
#define DC_FIXED_VALUE     0x08
#define B_BIT                 0
#define C_BIT                 1
#define D_BIT                 2

/*CLCD_Cursor_Display_Shift variable bits location*/
#define CDS_FIXED_VALUE     0x10
#define RL_BIT                 2

/*CLCD_Function_Set variable bits location*/
#define FS_FIXED_VALUE     0x20
#define F_BIT                 2
#define N_BIT                 3
#define DL_BIT                4

/*CLCD_Set_CGRAM_Function_Set*/
#define S_CGRAM_FIXED_VALUE     0x40

#define MAX_CGRAM_ADDRESS      0x3F

/*CLCD_Set_DDRAM_Function_Set*/
#define S_DDRAM_FIXED_VALUE              0x80
#define CLCD_LINE_FIRST_ADDRESS          0x00
#define CLCD_LINE_SECOND_ADDRESS         0x40

/*This mask is used to suppress the busy flag from the data bus value to be assigned to AC_Address*/
#define CLCD_READING_AC_ADDRESS_MASK     0x7F

//Used in HAL_CLCD_DisplayDecimalIntegerNumber
#define ASCII_OF_ZERO        48

//Used for the function HAL_CLCD_ConfigureDataBusDirection
#define LCD_DATA_BUS_OUTPUT    DIO_PIN_OUTPUT
#define LCD_DATA_BUS_INPUT     DIO_PIN_INPUT

//Used in HAL_CLCD_SendCommand
#define HIGH_NIBBLE_START      4

/*Required Command codes*/
#define CLCD_CLEAR             0x01
#define CLCD_CURSOR_HOME       0x02

#endif /* HAL_LCD_LCD_PRIVATE_H_ */
