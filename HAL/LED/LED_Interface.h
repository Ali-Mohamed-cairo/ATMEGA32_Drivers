/* 
 * File:   LED_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 4, 2024, 3:49 AM
 */

#ifndef LED_INTERFACE_H
#define	LED_INTERFACE_H


/**********************************Includes************************************/

#include <util/delay.h>

#include "../../BIT_MATH.h"
#include "../../Platform_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "LED_Config.h"

/**********************************MACROS**************************************/

#define _XTAL_FREQ              16000000 //For delay function

/*********************************REQUIRED ENUMS*******************************/

typedef enum{
    LED_PIN0 = 0,
    LED_PIN1,
    LED_PIN2,
    LED_PIN3,
    LED_PIN4,
    LED_PIN5,
    LED_PIN6,
    LED_PIN7
}LED_PIN_t;

typedef enum{
    LED_PORTA = 0,
    LED_PORTB,
    LED_PORTC,
    LED_PORTD,
    LED_PORTE
}LED_PORT_t;

typedef enum{
   LED_OFF = 0,
   LED_ON         
}LED_Status;
/*****************************Configuration structs****************************/

typedef struct{
    uint8 PORT_ID    : 3;
    uint8 Pin_Num    : 3;
    uint8 LED_Status : 1;/*ON or OFF*/
}LED_t;

typedef struct{
    uint8 PORT_ID   : 3;
    uint8 Start_Pin;
    uint8 End_Pin;
    uint8 Pattern_Value;/*It's given as binary value with each bit represents a led and 1 means ON but 0 means OFF*/
}LEDArray_t;

/***********************************APIs***************************************/

Std_ReturnType HAL_LED_LEDConfig(const LED_t *Copy_LED);
Std_ReturnType HAL_LED_LEDOn(LED_t *Copy_LED);
Std_ReturnType HAL_LED_LEDOff(LED_t *Copy_LED);
Std_ReturnType HAL_LED_LEDToggle(LED_t *Copy_LED);
Std_ReturnType HAL_LED_LEDBlink(LED_t *Copy_LED);// NOT implemented yet


Std_ReturnType HAL_LED_LEDArrayConfig(const LEDArray_t *Copy_LEDArray);
Std_ReturnType HAL_LED_LEDArrayPatternOn(const LEDArray_t *Copy_LEDArray);
Std_ReturnType HAL_LED_LEDArrayPatternOff(const LEDArray_t *Copy_LEDArray);
Std_ReturnType HAL_LED_LEDArrayPatternBlink(const LEDArray_t *Copy_LEDArray);// NOT implemented yet

#endif	/* LED_INTERFACE_H */

