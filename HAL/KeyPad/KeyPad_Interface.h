/* 
 * File:   KeyPad_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 1, 2024, 6:25 PM
 */

#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

/**<NOTE:
 * This driver apply a signal on each keypad row pins (row pins are connected  to output pins) 
 * then scan the keypad cloumns pins(columns pins are connecte to input pins).
*/

/**< LIB***/
#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"

/*< External files*/
#include "DIO_Interface.h"

/**< Keypad files***/
#include "KeyPad_Config.h" /*< Before using the driver, please enter this file to put your configurations*/

/**< Keypad unit*/
typedef struct{
    Pin_Conig_t KeyPad_Rows_Pins[KEYPAD_ROWS_NUM];
    Pin_Conig_t KeyPad_Cols_Pins[KEYPAD_COLS_NUM];
}KeyPad_t;

/**< APIS*/
Std_ReturnType HAL_KeyPad_KeyPadInit(KeyPad_t *Copy_KeyPadUnit);
Std_ReturnType HAL_KeyPad_KeyPadReadCharacter(const KeyPad_t *Copy_KeyPadUnit, uint8 *Copy_PressedBtn);
Std_ReturnType HAL_KeyPad_KeyPadReadNumber(const KeyPad_t *Copy_KeyPadUnit, uint8 *Copy_PressedNum);


#endif /*< KEYPAD_INTERFACE_H*/

