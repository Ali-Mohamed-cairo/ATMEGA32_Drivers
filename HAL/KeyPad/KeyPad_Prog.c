/* 
 * File:   KeyPad_Prog.c
 * Author: Ali Mohamed
 *
 * Created on March 1, 2024, 6:25 PM
 */

/**< LIB***/
#include <util/delay.h>

/**< Keypad files*/
#include "KeyPad_Interface.h"

Std_ReturnType HAL_KeyPad_KeyPadInit(KeyPad_t *Copy_KeyPadUnit)
{
    Std_ReturnType Local_ErrorState = E_NOT_OK;
    uint8 Local_Counter = 0;
    for(; Local_Counter < KEYPAD_ROWS_NUM; ++Local_Counter)
    {
        Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_Counter].Pin_Direction = DIO_PIN_OUTPUT;
        if(!MCAL_DIO_SetPinDirection(&(Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_Counter])))
        {
            Local_ErrorState = E_NOT_OK;
            break;
        }
        else
        {
            Local_ErrorState = E_OK;
        }
        if(!MCAL_DIO_SetPinValue(&(Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_Counter]), KEYPAD_PINS_NORMAL_STATE))
        {
            Local_ErrorState = E_NOT_OK;
            break;
        }
        else
        {
            Local_ErrorState = E_OK;
        }
    }
    if(E_NOT_OK == Local_ErrorState)
    {
        //Nothing to do, wrong implementation, head to return statment.
    }
    else
    {
        Local_Counter = 0;
        for(; Local_Counter < KEYPAD_COLS_NUM; ++Local_Counter)
        {
            Copy_KeyPadUnit->KeyPad_Cols_Pins[Local_Counter].Pin_Direction = KEYPAD_COLS_INPUT_MODE;
            if(!MCAL_DIO_SetPinDirection(&(Copy_KeyPadUnit->KeyPad_Cols_Pins[Local_Counter])))
            {
                Local_ErrorState = E_NOT_OK;
                break;
            }
            else
            {
                Local_ErrorState = E_OK;
            }
        }
    }
    return Local_ErrorState;
}
Std_ReturnType HAL_KeyPad_KeyPadReadCharacter(const KeyPad_t *Copy_KeyPadUnit, uint8 *Copy_PressedBtn)
{
    Std_ReturnType Local_ErrorState = E_NOT_OK;
    uint8 Local_RowsCounter = 0;
    uint8 Local_ColsCounter = 0;
    DIO_PIN_VALUE_t Local_ScanColVal = KEYPAD_PINS_NORMAL_STATE;
    *Copy_PressedBtn = '\0';
    for(; Local_RowsCounter < KEYPAD_ROWS_NUM; ++Local_RowsCounter)
    {
        if(!MCAL_DIO_TogglePinValue(&(Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_RowsCounter])))
        {
            Local_ErrorState = E_NOT_OK;
            break;
        }
        else
        {
            Local_ErrorState = E_OK;
        }
        for(; Local_ColsCounter < KEYPAD_COLS_NUM; ++Local_ColsCounter)
        {
           if(!MCAL_DIO_ReadPinValue(&(Copy_KeyPadUnit->KeyPad_Cols_Pins[Local_ColsCounter]), &Local_ScanColVal))
            {
                Local_ErrorState = E_NOT_OK;
                break;
            }
            else
            {
                Local_ErrorState = E_OK;
                if(!(KEYPAD_PINS_NORMAL_STATE) == Local_ScanColVal)
                {
                    _delay_ms(KEYPAD_DEBOUNCING_TIME);
                    while(!(KEYPAD_PINS_NORMAL_STATE) == Local_ScanColVal)
                    {
                        MCAL_DIO_ReadPinValue(&(Copy_KeyPadUnit->KeyPad_Cols_Pins[Local_ColsCounter]), &Local_ScanColVal);
                    }
                    *Copy_PressedBtn = Local_KeyPadLayout[Local_RowsCounter][Local_ColsCounter];
                    break;
                }
                else
                {
                    //Nothing to do, because nothing is pressed.
                }
            } 
        }
        Local_ColsCounter = 0;
        MCAL_DIO_TogglePinValue(&(Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_RowsCounter]));
    }
    return Local_ErrorState;
}
Std_ReturnType HAL_KeyPad_KeyPadReadNumber(const KeyPad_t *Copy_KeyPadUnit, uint8 *Copy_PressedNum)
{
    Std_ReturnType Local_ErrorState = E_NOT_OK;
    uint8 Local_RowsCounter = 0;
    uint8 Local_ColsCounter = 0;
    DIO_PIN_VALUE_t Local_ScanColVal = KEYPAD_PINS_NORMAL_STATE;
    *Copy_PressedNum = '\0';
    for(; Local_RowsCounter < KEYPAD_ROWS_NUM; ++Local_RowsCounter)
    {
        if(!MCAL_DIO_TogglePinValue(&(Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_RowsCounter])))
        {
            Local_ErrorState = E_NOT_OK;
            break;
        }
        else
        {
            Local_ErrorState = E_OK;
        }
        for(; Local_ColsCounter < KEYPAD_COLS_NUM; ++Local_ColsCounter)
        {
           if(!MCAL_DIO_ReadPinValue(&(Copy_KeyPadUnit->KeyPad_Cols_Pins[Local_ColsCounter]), &Local_ScanColVal))
            {
                Local_ErrorState = E_NOT_OK;
                break;
            }
            else
            {
                Local_ErrorState = E_OK;
                if(!(KEYPAD_PINS_NORMAL_STATE) == Local_ScanColVal)
                {
                    _delay_ms(KEYPAD_DEBOUNCING_TIME);
                    while(!(KEYPAD_PINS_NORMAL_STATE) == Local_ScanColVal)
                    {
                        MCAL_DIO_ReadPinValue(&(Copy_KeyPadUnit->KeyPad_Cols_Pins[Local_ColsCounter]), &Local_ScanColVal);
                    }
                    *Copy_PressedNum = Local_KeyPadLayout[Local_RowsCounter][Local_ColsCounter] - 48;
                    break;
                }
                else
                {
                    //Nothing to do, because nothing is pressed.
                }
            } 
        }
        Local_ColsCounter = 0;
        MCAL_DIO_TogglePinValue(&(Copy_KeyPadUnit->KeyPad_Rows_Pins[Local_RowsCounter]));
    }
    return Local_ErrorState;
}
