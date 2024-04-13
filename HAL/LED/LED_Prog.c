/* 
 * File:   LED_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 4, 2024, 3:49 AM
 */


#include "LED_Interface.h"


/******************************Single LED APIs************************************/


Std_ReturnType HAL_LED_LEDConfig(const LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    if(Copy_LED->PORT_ID > LED_PORTE || Copy_LED->Pin_Num > LED_PIN7)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        Pin_Conig_t LED = {
            .PORT_ID = Copy_LED->PORT_ID,
            .Pin_Num = Copy_LED->Pin_Num,
            .Pin_Direction = DIO_PIN_OUTPUT,
            .Pin_Value = Copy_LED->LED_Status
        };
        if(!MCAL_DIO_SetPinDirection(&LED))
        {
           Local_ErrorStatus = E_NOT_OK; 
        }
        else if(!MCAL_DIO_SetPinValue(&LED, LED.Pin_Value))
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
Std_ReturnType HAL_LED_LEDOn(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_Status
    };
    if(!MCAL_DIO_SetPinValue(&LED, LED_ON))
    {
       Local_ErrorStatus = E_NOT_OK; 
    }
    else
    {
        Copy_LED->LED_Status = LED.Pin_Value;
        Local_ErrorStatus = E_OK;
    }  
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDOff(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_Status
    };
    if(!MCAL_DIO_SetPinValue(&LED, LED_OFF))
    {
       Local_ErrorStatus = E_NOT_OK; 
    }
    else
    {
        Copy_LED->LED_Status = LED.Pin_Value;
        Local_ErrorStatus = E_OK;
    }
    
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDToggle(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_Status
    };
    if(!MCAL_DIO_TogglePinValue(&LED))
    {
       Local_ErrorStatus = E_NOT_OK; 
    }
    else
    {
        Copy_LED->LED_Status = LED.Pin_Value;
        Local_ErrorStatus = E_OK;
    }
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDBlink(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    uint8 Local_BlinkingTimes = BLINKING_TIMES;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_Status
    };
    for(; Local_BlinkingTimes > 0; --Local_BlinkingTimes)
    {
       if(!MCAL_DIO_TogglePinValue(&LED)) 
       {
           Local_ErrorStatus = E_NOT_OK;
       }
       else
       {
           Copy_LED->LED_Status = LED.Pin_Value;
           Local_ErrorStatus = E_OK;
       }
        _delay_ms(BLINKING_DELAY);
        MCAL_DIO_TogglePinValue(&LED);
        _delay_ms(BLINKING_DELAY);
    }
    return Local_ErrorStatus;
}

/****************************LED Array APIs***************************************/

Std_ReturnType HAL_LED_LEDArrayConfig(const LEDArray_t *Copy_LEDArray)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    if(Copy_LEDArray->PORT_ID > LED_PORTE || Copy_LEDArray->End_Pin > LED_PIN7)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        sint8 Local_Pin_Num = (Copy_LEDArray->End_Pin);
        for(; Local_Pin_Num >= (Copy_LEDArray->Start_Pin); --Local_Pin_Num)
        {
            Pin_Conig_t LED = {
                .PORT_ID = Copy_LEDArray->PORT_ID,
                .Pin_Num = Local_Pin_Num - 1,
                .Pin_Direction = DIO_PIN_OUTPUT,
            };
            if(!MCAL_DIO_SetPinDirection(&LED))
            {
                Local_ErrorStatus = E_NOT_OK;
            }
            else
            {
                Local_ErrorStatus = E_OK;
            }
        }
    }
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDArrayPatternOn(const LEDArray_t *Copy_LEDArray)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    uint8 Local_LEDStatus = LED_OFF;
    sint8 Local_Pin_Num = (Copy_LEDArray->End_Pin);
    for(; Local_Pin_Num >= (Copy_LEDArray->Start_Pin); Local_Pin_Num--)
    {
        Local_LEDStatus = GET_BIT(Copy_LEDArray->Pattern_Value, Local_Pin_Num);
        Pin_Conig_t LED = {
            .PORT_ID = Copy_LEDArray->PORT_ID,
            .Pin_Num = Local_Pin_Num,
            .Pin_Direction = DIO_PIN_OUTPUT,
            .Pin_Value = Local_LEDStatus
        };
        if(!MCAL_DIO_SetPinValue(&LED, LED.Pin_Value))
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
Std_ReturnType HAL_LED_LEDArrayPatternOff(const LEDArray_t *Copy_LEDArray)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    sint8 Local_Pin_Num = (Copy_LEDArray->End_Pin);
    for(; Local_Pin_Num >= (Copy_LEDArray->Start_Pin); Local_Pin_Num--)
    {
        Pin_Conig_t LED = {
            .PORT_ID = Copy_LEDArray->PORT_ID,
            .Pin_Num = Local_Pin_Num,
            .Pin_Direction = DIO_PIN_OUTPUT,
            .Pin_Value = LED_OFF
        };
        if(!MCAL_DIO_SetPinValue(&LED, LED.Pin_Value))
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
Std_ReturnType HAL_LED_LEDArrayPatternBlink(const LEDArray_t *Copy_LEDArray)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    sint8 Local_BlinkingTimes = BLINKING_TIMES;
    for(; Local_BlinkingTimes > 0; Local_BlinkingTimes--)
    {
        HAL_LED_LEDArrayPatternOn(Copy_LEDArray);
        _delay_ms(BLINKING_DELAY);
        HAL_LED_LEDArrayPatternOff(Copy_LEDArray);
        _delay_ms(BLINKING_DELAY);
        Local_ErrorStatus = E_OK;
    }
    return Local_ErrorStatus;
}
