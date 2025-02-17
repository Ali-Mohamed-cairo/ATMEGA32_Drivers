/* 
 * File:   LED_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 4, 2024, 3:49 AM
 */


#include "LED_Interface.h"


/******************************Single LED APIs************************************/


Std_ReturnType HAL_LED_LEDConfig(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Copy_LED->LED_LastStatus = LED_OFF;
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
            .Pin_Value = Copy_LED->LED_LastStatus
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
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDOn(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Copy_LED->LED_LastStatus = (Copy_LED->LED_Connection == MC_Source)? DIO_HIGH : DIO_LOW;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_LastStatus
    };
    if(!MCAL_DIO_SetPinValue(&LED, Copy_LED->LED_LastStatus))
    {
       Local_ErrorStatus = E_NOT_OK; 
    }
    else
    {
        Local_ErrorStatus = E_OK;
    }  
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDOff(LED_t *Copy_LED)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Copy_LED->LED_LastStatus = (Copy_LED->LED_Connection == MC_Source)? DIO_LOW : DIO_HIGH;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_LastStatus
    };
    if(!MCAL_DIO_SetPinValue(&LED, Copy_LED->LED_LastStatus))
    {
       Local_ErrorStatus = E_NOT_OK; 
    }
    else
    {
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
        .Pin_Value = Copy_LED->LED_LastStatus
    };
    if(!MCAL_DIO_TogglePinValue(&LED))
    {
       Local_ErrorStatus = E_NOT_OK; 
    }
    else
    {
        Copy_LED->LED_LastStatus = LED.Pin_Value;
        Local_ErrorStatus = E_OK;
    }
    return Local_ErrorStatus;
}
Std_ReturnType HAL_LED_LEDBlink(LED_t *Copy_LED, uint8 Copy_BlinkingTimes)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    Pin_Conig_t LED = {
        .PORT_ID = Copy_LED->PORT_ID,
        .Pin_Num = Copy_LED->Pin_Num,
        .Pin_Direction = DIO_PIN_OUTPUT,
        .Pin_Value = Copy_LED->LED_LastStatus
    };
    for(; Copy_BlinkingTimes > 0; --Copy_BlinkingTimes)
    {
       if(!MCAL_DIO_TogglePinValue(&LED)) 
       {
           Local_ErrorStatus = E_NOT_OK;
       }
       else
       {
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
    uint8 Local_BitValue = 0;
    sint8 Local_Pin_Num = (Copy_LEDArray->End_Pin);
    for(; Local_Pin_Num >= (Copy_LEDArray->Start_Pin); Local_Pin_Num--)
    {
    	Local_BitValue = GET_BIT(Copy_LEDArray->Pattern_Value, Local_Pin_Num);
    	Local_LEDStatus = (Copy_LEDArray->LEDs_Connection == MC_Source)? Local_BitValue : (!Local_BitValue);
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
    uint8 Local_LEDStatus = LED_OFF;
    sint8 Local_Pin_Num = (Copy_LEDArray->End_Pin);
    for(; Local_Pin_Num >= (Copy_LEDArray->Start_Pin); Local_Pin_Num--)
    {
    	Local_LEDStatus = (Copy_LEDArray->LEDs_Connection == MC_Source)? DIO_LOW : DIO_HIGH;
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
Std_ReturnType HAL_LED_LEDArrayPatternBlink(const LEDArray_t *Copy_LEDArray, uint8 Copy_BlinkingTimes)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    for(; Copy_BlinkingTimes > 0; Copy_BlinkingTimes--)
    {
        HAL_LED_LEDArrayPatternOn(Copy_LEDArray);
        _delay_ms(BLINKING_DELAY);
        HAL_LED_LEDArrayPatternOff(Copy_LEDArray);
        _delay_ms(BLINKING_DELAY);
        Local_ErrorStatus = E_OK;
    }
    return Local_ErrorStatus;
}
