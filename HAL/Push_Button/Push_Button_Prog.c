/* 
 * File:   Push_Button_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 5, 2024, 11:05 AM
 */



#include <util/delay.h>

#include "Push_Button_Interface.h"



Std_ReturnType HAL_Push_Button_BtnConfig(const PushBtn_t *Copy_Btn)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    if(Copy_Btn->PORT_ID > Btn_PORTE || Copy_Btn->Pin_Num > Btn_PIN7)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        Pin_Conig_t Btn = {
            .PORT_ID = Copy_Btn->PORT_ID,
            .Pin_Num = Copy_Btn->Pin_Num,
            .Pin_Direction = DIO_PIN_INPUT,
            .Pin_Value = Copy_Btn->Last_Status
        };
        if(!MCAL_DIO_SetPinDirection(&Btn))
        {
            Local_ErrorStatus = E_NOT_OK;
        }
        else
        {
            Local_ErrorStatus = E_OK;
        }
    }
    return Local_ErrorStatus;
}
Std_ReturnType HAL_Push_Button_ReadBtn(PushBtn_t *Copy_Btn, uint8 *Copy_BtnStatus)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    uint8 Local_BtnStatus = INITIAL_VALUE;
    Pin_Conig_t Btn = {
            .PORT_ID = Copy_Btn->PORT_ID,
            .Pin_Num = Copy_Btn->Pin_Num,
            .Pin_Direction = DIO_PIN_INPUT,
            .Pin_Value = Copy_Btn->Last_Status
    };
    if(!MCAL_DIO_ReadPinValue(&Btn, &Local_BtnStatus))
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        if(Copy_Btn->Connection_Meth == PULL_DOWN_Connection)
        {
            if(Local_BtnStatus == Btn_D_Pressed)
            {
                _delay_ms(PUSH_BTN_DEBOUNCING_TIME);
                while(Local_BtnStatus != Btn_D_Released)
                {
                    MCAL_DIO_ReadPinValue(&Btn, &Local_BtnStatus);
                }
                *Copy_BtnStatus = Btn_D_Pressed;
                Copy_Btn->Last_Status = Btn_D_Pressed;
            }
            else
            {
                *Copy_BtnStatus = Btn_D_Released;
                Copy_Btn->Last_Status = Btn_D_Released;
            }
        }
        else if(Copy_Btn->Connection_Meth == PULL_UP_Connection)
        {
            if(Local_BtnStatus == Btn_U_Pressed)
            {
                _delay_ms(PUSH_BTN_DEBOUNCING_TIME);
                while(Local_BtnStatus != Btn_U_Released)
                {
                    MCAL_DIO_ReadPinValue(&Btn, &Local_BtnStatus);
                }
                *Copy_BtnStatus = Btn_U_Pressed;
                Copy_Btn->Last_Status = Btn_U_Pressed;
            }
            else
            {
                *Copy_BtnStatus = Btn_U_Released;
                Copy_Btn->Last_Status = Btn_U_Released;
            }
        }
        Local_ErrorStatus = E_OK;
    }
    return Local_ErrorStatus;
}
