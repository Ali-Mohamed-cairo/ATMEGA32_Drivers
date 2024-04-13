/* 
 * File:   DIO_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 1, 2024, 6:25 PM
 */

#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

/**< External files*/
#include "DIO_Interface.h"

/**< MACROS***/

/**< Choose between : 1- DIO_PIN_INPUT
 *                    2- DIO_PIN_INPUT_PULL_UP (If present in your used MC)
 *                    (You can add different modes according to your used MC I/O peripheral)
 */
#define KEYPAD_COLS_INPUT_MODE     DIO_PIN_INPUT

#define KEYPAD_PINS_NORMAL_STATE   DIO_LOW

#define KEYPAD_DEBOUNCING_TIME     120     //Milisecond

#define LAYOUT_1                   0
#define LAYOUT_2                   1
#define LAYOUT_3                   2
#define LAYOUT_4                   4
#define PRIVATE_LAYOUT
#define USED_KEY_PAD_LAYOUT        LAYOUT_1


/*< Your KeyPad layout. ADD YOURS IF IT IS NOT PRESENT*/
#if (USED_KEY_PAD_LAYOUT == LAYOUT_1)
#define KEYPAD_ROWS_NUM            0x4
#define KEYPAD_COLS_NUM            0x4
static const uint8 Local_KeyPadLayout[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = {{'1', '2', '3', 'A'},
																		   {'4', '5', '6', 'B'},
																		   {'7', '8', '9', 'C'},
																		   {'*', '0', '#', 'D'}};

#elif (USED_KEY_PAD_LAYOUT == LAYOUT_2)
#define KEYPAD_ROWS_NUM            0x4
#define KEYPAD_COLS_NUM            0x3
static const uint8 Local_KeyPadLayout[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = {{'1', '2', '3'},
                                                              	  	  	   {'4', '5', '6'},
																		   {'7', '8', '9'},
																		   {'*', '0', '#'}};

#elif (USED_KEY_PAD_LAYOUT == LAYOUT_3)
#define KEYPAD_ROWS_NUM            0x4
#define KEYPAD_COLS_NUM            0x3
static const uint8 Local_KeyPadLayout[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = {{'1', '2', '3'},
                                                              	  	  	   {'4', '5', '6'},
																		   {'7', '8', '9'},
																		   {'\0', '0', '\0'}};

#elif (USED_KEY_PAD_LAYOUT == LAYOUT_4)
#define KEYPAD_ROWS_NUM            0x4
#define KEYPAD_COLS_NUM            0x4
static const uint8 Local_KeyPadLayout[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = {{'7', '8', '9', '/'},
                                                              	  	  	   {'4', '5', '6', '*'},
																		   {'1', '2', '3', '-'},
																		   {'.', '0', '=', '+'}};

#else /*< ADD YOUR LAYOUT HERE WITH THE SAME ARRAY NAME AND DECLARATION SYTLE*/
#define KEYPAD_ROWS_NUM            
#define KEYPAD_COLS_NUM            
/*< HERE*/                 

#endif /*< USED_KEY_PAD_LAYOUT*/

#endif /*<KEYPAD_CONFIG_H*/
