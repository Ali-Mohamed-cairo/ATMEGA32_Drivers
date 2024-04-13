/* 
 * File:   DIO_Prog.c
 * Author: Ali Mohamed
 *
 * Created on March 1, 2024, 6:25 PM
*/
/*********************************Includes*************************************/

#include "DIO_Interface.h"

/**********************************Pin APIs************************************/

#if(APIs_CONFIG == PIN_APIs_CONFIG || APIs_CONFIG == PORT_PIN_APIs_CONFIG)
Std_ReturnType MCAL_DIO_SetPinDirection(const Pin_Conig_t *Copy_PinInfo)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PinInfo->Pin_Num > DIO_PIN7)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PinInfo->PORT_ID)
        {
            case DIO_PORTA:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinInfo->Pin_Direction)
                {
                    case DIO_PIN_OUTPUT:
                        SET_BIT(DDRA_REG.DDRA_REGISTER, Copy_PinInfo->Pin_Num);
                        break;
                    case DIO_PIN_INPUT:
                        CLEAR_BIT(DDRA_REG.DDRA_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTA_REG.PORTA_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    case DIO_PIN_INPUT_PULL_UP:
                        CLEAR_BIT(DDRA_REG.DDRA_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTA_REG.PORTA_REGISTER, Copy_PinInfo->Pin_Num);
                        CLEAR_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            case DIO_PORTB:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinInfo->Pin_Direction)
                {
                    case DIO_PIN_OUTPUT:
                        SET_BIT(DDRB_REG.DDRB_REGISTER, Copy_PinInfo->Pin_Num);
                        break;
                    case DIO_PIN_INPUT:
                        CLEAR_BIT(DDRB_REG.DDRB_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTB_REG.PORTB_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    case DIO_PIN_INPUT_PULL_UP:
                        CLEAR_BIT(DDRB_REG.DDRB_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTB_REG.PORTB_REGISTER, Copy_PinInfo->Pin_Num);
                        CLEAR_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            case DIO_PORTC:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinInfo->Pin_Direction)
                {
                    case DIO_PIN_OUTPUT:
                        SET_BIT(DDRC_REG.DDRC_REGISTER, Copy_PinInfo->Pin_Num);
                        break;
                    case DIO_PIN_INPUT:
                        CLEAR_BIT(DDRC_REG.DDRC_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTC_REG.PORTC_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    case DIO_PIN_INPUT_PULL_UP:
                        CLEAR_BIT(DDRC_REG.DDRC_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTC_REG.PORTC_REGISTER, Copy_PinInfo->Pin_Num);
                        CLEAR_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            case DIO_PORTD:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinInfo->Pin_Direction)
                {
                    case DIO_PIN_OUTPUT:
                        SET_BIT(DDRD_REG.DDRD_REGISTER, Copy_PinInfo->Pin_Num);
                        break;
                    case DIO_PIN_INPUT:
                        CLEAR_BIT(DDRD_REG.DDRD_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTD_REG.PORTD_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    case DIO_PIN_INPUT_PULL_UP:
                        CLEAR_BIT(DDRC_REG.DDRC_REGISTER, Copy_PinInfo->Pin_Num);
                        SET_BIT(PORTC_REG.PORTC_REGISTER, Copy_PinInfo->Pin_Num);
                        CLEAR_BIT(SFIOR_REG, PUB_BIT);
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }
    }
    return Local_ErrorStatus;
}

Std_ReturnType MCAL_DIO_GetPinDirection(const Pin_Conig_t *Copy_PinInfo, DIO_PIN_DIRECTION_t *Copy_Direction)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    uint8 Local_PinDirection = INITIAL_VALUE;
    if(Copy_PinInfo->Pin_Num > DIO_PIN7)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
         switch(Copy_PinInfo->PORT_ID)
        {   
            case DIO_PORTA:
                Local_PinDirection = GET_BIT(DDRA_REG.DDRA_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinDirection == DIO_PIN_INPUT || Local_PinDirection == DIO_PIN_OUTPUT)
                {
                    *Copy_Direction = Local_PinDirection;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                    Local_ErrorStatus = E_NOT_OK;   
                }
                break;
            case DIO_PORTB:
                Local_PinDirection = GET_BIT(DDRB_REG.DDRB_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinDirection == DIO_PIN_INPUT || Local_PinDirection == DIO_PIN_OUTPUT)
                {
                    *Copy_Direction = Local_PinDirection;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                    Local_ErrorStatus = E_NOT_OK;   
                }
                break;
            case DIO_PORTC:
                Local_PinDirection = GET_BIT(DDRC_REG.DDRC_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinDirection == DIO_PIN_INPUT || Local_PinDirection == DIO_PIN_OUTPUT)
                {
                    *Copy_Direction = Local_PinDirection;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                    Local_ErrorStatus = E_NOT_OK;   
                }
                break;
            case DIO_PORTD:
                Local_PinDirection = GET_BIT(DDRD_REG.DDRD_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinDirection == DIO_PIN_INPUT || Local_PinDirection == DIO_PIN_OUTPUT)
                {
                    *Copy_Direction = Local_PinDirection;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                    Local_ErrorStatus = E_NOT_OK;   
                }
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }
    }
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_SetPinValue(Pin_Conig_t *Copy_PinInfo, DIO_PIN_VALUE_t Copy_PinValue)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PinInfo->Pin_Num > DIO_PIN7 || Copy_PinInfo->Pin_Direction == DIO_PIN_INPUT)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PinInfo->PORT_ID)
        {
            case DIO_PORTA:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinValue)
                {
                    case DIO_HIGH:
                        SET_BIT(PORTA_REG.PORTA_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    case DIO_LOW:
                        CLEAR_BIT(PORTA_REG.PORTA_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            case DIO_PORTB:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinValue)
                {
                    case DIO_HIGH:
                        SET_BIT(PORTB_REG.PORTB_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    case DIO_LOW:
                        CLEAR_BIT(PORTB_REG.PORTB_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            case DIO_PORTC:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinValue)
                {
                    case DIO_HIGH:
                        SET_BIT(PORTC_REG.PORTC_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    case DIO_LOW:
                        CLEAR_BIT(PORTC_REG.PORTC_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            case DIO_PORTD:
                Local_ErrorStatus = E_OK;
                switch(Copy_PinValue)
                {
                    case DIO_HIGH:
                        SET_BIT(PORTD_REG.PORTD_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    case DIO_LOW:
                        CLEAR_BIT(PORTD_REG.PORTD_REGISTER, Copy_PinInfo->Pin_Num);
                        Copy_PinInfo->Pin_Value = Copy_PinValue;
                        break;
                    default:
                        Local_ErrorStatus = E_NOT_OK;
                        break;
                }
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }
    }
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_ReadPinValue(const Pin_Conig_t *Copy_PinInfo, DIO_PIN_VALUE_t *Copy_PinValue)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    uint8 Local_PinValue = INITIAL_VALUE;
    if(Copy_PinInfo->Pin_Num > DIO_PIN7 || Copy_PinInfo->Pin_Direction == DIO_PIN_OUTPUT)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PinInfo->PORT_ID)
        {
            case DIO_PORTA:
                Local_PinValue = GET_BIT(PINA_REG.PINA_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinValue == DIO_HIGH || Local_PinValue == DIO_LOW)
                {
                    *Copy_PinValue = Local_PinValue;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                   Local_ErrorStatus = E_NOT_OK; 
                }
                break;
            case DIO_PORTB:
                Local_PinValue = GET_BIT(PINB_REG.PINB_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinValue == DIO_HIGH || Local_PinValue == DIO_LOW)
                {
                    *Copy_PinValue = Local_PinValue;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                   Local_ErrorStatus = E_NOT_OK; 
                }
                break;
            case DIO_PORTC:
                Local_PinValue = GET_BIT(PINC_REG.PINC_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinValue == DIO_HIGH || Local_PinValue == DIO_LOW)
                {
                    *Copy_PinValue = Local_PinValue;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                   Local_ErrorStatus = E_NOT_OK; 
                }
                break;
            case DIO_PORTD:
                Local_PinValue = GET_BIT(PIND_REG.PIND_REGISTER, Copy_PinInfo->Pin_Num);
                if(Local_PinValue == DIO_HIGH || Local_PinValue == DIO_LOW)
                {
                    *Copy_PinValue = Local_PinValue;
                    Local_ErrorStatus = E_OK;
                }
                else
                {
                   Local_ErrorStatus = E_NOT_OK; 
                }
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }  
    }
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_TogglePinValue(Pin_Conig_t *Copy_PinInfo)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    if(Copy_PinInfo->Pin_Num > DIO_PIN7 || Copy_PinInfo->Pin_Direction == DIO_PIN_INPUT)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PinInfo->PORT_ID)
        {
            case DIO_PORTA:
                TOGGLE_BIT(PORTA_REG.PORTA_REGISTER, Copy_PinInfo->Pin_Num);
                Copy_PinInfo->Pin_Value = ~(Copy_PinInfo->Pin_Value);
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTB:
                TOGGLE_BIT(PORTB_REG.PORTB_REGISTER, Copy_PinInfo->Pin_Num);
                Copy_PinInfo->Pin_Value = ~(Copy_PinInfo->Pin_Value);
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTC:         
                TOGGLE_BIT(PORTC_REG.PORTC_REGISTER, Copy_PinInfo->Pin_Num);
                Copy_PinInfo->Pin_Value = ~(Copy_PinInfo->Pin_Value);
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTD:
                TOGGLE_BIT(PORTD_REG.PORTD_REGISTER, Copy_PinInfo->Pin_Num);
                Copy_PinInfo->Pin_Value = ~(Copy_PinInfo->Pin_Value);
                Local_ErrorStatus = E_OK;
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }  
    }
    return Local_ErrorStatus;
}

Std_ReturnType MCAL_DIO_InitializePinOutput(const Pin_Conig_t *Copy_PinInfo)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK;
    if(Copy_PinInfo->Pin_Num > DIO_PIN7 || Copy_PinInfo->Pin_Direction == DIO_PIN_INPUT)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        MCAL_DIO_SetPinDirection(Copy_PinInfo);
        MCAL_DIO_SetPinValue(Copy_PinInfo, DIO_LOW);
    }
    return Local_ErrorStatus;
}

#endif /*APIs_CONFIG*/

/*********************************Port APIs************************************/

#if(APIs_CONFIG == PORT_APIs_CONFIG || APIs_CONFIG == PORT_PIN_APIs_CONFIG)

Std_ReturnType MCAL_DIO_SetPortDirection(const Port_Conig_t *Copy_PortInfo)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PortInfo->PORT_ID > DIO_PORTE)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
       switch(Copy_PortInfo->PORT_ID)
       {
           case DIO_PORTA:
               DDRA_REG.DDRA_REGISTER = Copy_PortInfo->Port_Direction;
               Local_ErrorStatus = E_OK;
               break;
           case DIO_PORTB:
               DDRB_REG.DDRB_REGISTER = Copy_PortInfo->Port_Direction;
               Local_ErrorStatus = E_OK;
               break;
           case DIO_PORTC:
               DDRC_REG.DDRC_REGISTER = Copy_PortInfo->Port_Direction;
               Local_ErrorStatus = E_OK;
               break;
           case DIO_PORTD:
               DDRD_REG.DDRD_REGISTER = Copy_PortInfo->Port_Direction;
               Local_ErrorStatus = E_OK;
               break;
           default:
               Local_ErrorStatus = E_NOT_OK;
               break;
       }   
    }
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_GetPortDirection(const Port_Conig_t *Copy_PortInfo, uint8 *Copy_Direction)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PortInfo->PORT_ID > DIO_PORTE)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PortInfo->PORT_ID)
        {
            case DIO_PORTA:
                *Copy_Direction = DDRA_REG.DDRA_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTB:
                *Copy_Direction = DDRB_REG.DDRB_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTC:
                *Copy_Direction = DDRC_REG.DDRC_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTD:
                *Copy_Direction = DDRD_REG.DDRD_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }
    }
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_SetPortValue(Port_Conig_t *Copy_PortInfo, const uint8 Copy_PortValue)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PortInfo->PORT_ID > DIO_PORTE)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
       switch(Copy_PortInfo->PORT_ID)
       {
           case DIO_PORTA:
               PORTA_REG.PORTA_REGISTER = Copy_PortValue;
               Copy_PortInfo->Port_Value = Copy_PortValue;
               Local_ErrorStatus = E_OK;
               break;
           case DIO_PORTB:
               PORTB_REG.PORTB_REGISTER = Copy_PortValue;
               Copy_PortInfo->Port_Value = Copy_PortValue;
               Local_ErrorStatus = E_OK;
               break;
           case DIO_PORTC:
               PORTC_REG.PORTC_REGISTER = Copy_PortValue;
               Copy_PortInfo->Port_Value = Copy_PortValue;
               Local_ErrorStatus = E_OK;
               break;
           case DIO_PORTD:
               PORTD_REG.PORTD_REGISTER = Copy_PortValue;
               Copy_PortInfo->Port_Value = Copy_PortValue;
               Local_ErrorStatus = E_OK;
               break;
           default:
               Local_ErrorStatus = E_NOT_OK;
               break;
       }   
    }
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_ReadPortValue(const Port_Conig_t *Copy_PortInfo, uint8 *Copy_PortValue)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PortInfo->PORT_ID > DIO_PORTE)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PortInfo->PORT_ID)
        {
            case DIO_PORTA:
                *Copy_PortValue = PINA_REG.PINA_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTB:
                *Copy_PortValue = PINB_REG.PINB_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTC:
                *Copy_PortValue = PINC_REG.PINC_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTD:
                *Copy_PortValue = PIND_REG.PIND_REGISTER;
                Local_ErrorStatus = E_OK;
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }
    }
    
    return Local_ErrorStatus;
}
Std_ReturnType MCAL_DIO_TogglePortValue(Port_Conig_t *Copy_PortInfo)
{
    Std_ReturnType Local_ErrorStatus = E_NOT_OK; 
    if(Copy_PortInfo->PORT_ID > DIO_PORTE)
    {
        Local_ErrorStatus = E_NOT_OK;
    }
    else
    {
        switch(Copy_PortInfo->PORT_ID)
        {
            case DIO_PORTA:
            	PORTA_REG.PORTA_REGISTER = ~(Copy_PortInfo->Port_Value);
                Copy_PortInfo->Port_Value = ~(Copy_PortInfo->Port_Value);
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTB:
            	PORTB_REG.PORTB_REGISTER = ~(Copy_PortInfo->Port_Value);
                Copy_PortInfo->Port_Value = ~(Copy_PortInfo->Port_Value);
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTC:
            	PORTC_REG.PORTC_REGISTER = ~(Copy_PortInfo->Port_Value);
                Copy_PortInfo->Port_Value = ~(Copy_PortInfo->Port_Value);
                Local_ErrorStatus = E_OK;
                break;
            case DIO_PORTD:
            	PORTD_REG.PORTD_REGISTER = ~(Copy_PortInfo->Port_Value);
                Copy_PortInfo->Port_Value = ~(Copy_PortInfo->Port_Value);
                Local_ErrorStatus = E_OK;
                break;
            default:
                Local_ErrorStatus = E_NOT_OK;
                break;
        }
    }
    return Local_ErrorStatus;
}
#endif /*APIs_CONFIG*/
