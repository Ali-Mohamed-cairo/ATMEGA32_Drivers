/* 
 * File:   DIO_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 1, 2024, 6:25 PM
 */

#ifndef DIO_INTERFACE_H
#define	DIO_INTERFACE_H

/**********************************Includes************************************/

#include "../../BIT_MATH.h"
#include "DIO_Config.h"
#include "DIO_Private.h"

/**********************************MACROS**************************************/
#define INITIAL_VALUE           6    /*Aimless random value*/
#define INPUT_PORT              0xFF
#define OUTPUT_PORT             0x00
#define PORT_HIGH               0xFF
#define PORT_LOW                0x00

/*********************************REQUIRED ENUMS*******************************/

typedef enum{
    DIO_PIN0 = 0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
}DIO_PIN_t;

typedef enum{
    DIO_PORTA = 0,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PORTD,
    DIO_PORTE
}DIO_PORT_t;

typedef enum{
    DIO_PIN_OUTPUT = 0,
    DIO_PIN_INPUT,
	DIO_PIN_INPUT_PULL_UP
}DIO_PIN_DIRECTION_t;

typedef enum{
    DIO_LOW = 0,
    DIO_HIGH
}DIO_PIN_VALUE_t;

/*****************************Configuration structs****************************/
/*
 * We use this structs to configure any pin or port by taking an object of it, then
 * fill this struct members with the needed specs of the pin/port. Sending this object
 * to any of the APIs is done by "Reference(&Pin_object)"
*/
typedef struct{
    uint8 PORT_ID       : 2;
    uint8 Pin_Num       : 3;
    uint8 Pin_Direction : 2;
    uint8 Pin_Value     : 1;
}Pin_Conig_t;

typedef struct{
    uint8 PORT_ID : 3;
    uint8 Port_Value;
    uint8 Port_Direction;
    /*From options : "INPUT_PORT" or "OUTPUT_PORT" or any char value where 0 bit 
     * corresponds to input pin  while 1 bit corresponds to output pin
     */
}Port_Conig_t;

/***********************************APIs***************************************/

Std_ReturnType MCAL_DIO_SetPinDirection(const Pin_Conig_t *Copy_PinInfo);
Std_ReturnType MCAL_DIO_GetPinDirection(const Pin_Conig_t *Copy_PinInfo, DIO_PIN_DIRECTION_t *Copy_Direction);
Std_ReturnType MCAL_DIO_SetPinValue( Pin_Conig_t *Copy_PinInfo, DIO_PIN_VALUE_t Copy_PinValue);
Std_ReturnType MCAL_DIO_ReadPinValue(const Pin_Conig_t *Copy_PinInfo, DIO_PIN_VALUE_t *Copy_PinValue);
Std_ReturnType MCAL_DIO_TogglePinValue(Pin_Conig_t *Copy_PinInfo);
Std_ReturnType MCAL_DIO_InitializePinOutput(const Pin_Conig_t *Copy_PinInfo);

Std_ReturnType MCAL_DIO_SetPortDirection(const Port_Conig_t *Copy_PortInfo);
Std_ReturnType MCAL_DIO_GetPortDirection(const Port_Conig_t *Copy_PortInfo, uint8 *Copy_Direction);
Std_ReturnType MCAL_DIO_SetPortValue(Port_Conig_t *Copy_PortInfo, const uint8 Copy_PortValue);
Std_ReturnType MCAL_DIO_ReadPortValue(const Port_Conig_t *Copy_PortInfo, uint8 *Copy_PortValue);
Std_ReturnType MCAL_DIO_TogglePortValue(Port_Conig_t *Copy_PortInfo);

#endif	/* DIO_INTERFACE_H */

