/* 
 * File:   EXT_Interrupt_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 6, 2024, 12:46 PM
 */

#ifndef EXT_INTERRUPT_INTERFACE_H
#define	EXT_INTERRUPT_INTERFACE_H

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"


/*EXTERNAL INTERRUPT REQUIRED*/
typedef enum{
    EXTINT2 = 5,/*Pin RB0(Pin 2 port D). It has no priority bit because it always has high priority.*/
    EXTINT0,   /*Pin RB1(Pin 3 port D)*/
    EXTINT1    /*Pin RB2(Pin 2 port B)*/
}EXINT_t;

typedef enum{
	LOW_LEVEL = 0, /*Available for INT0/1 only BUT NOT INT2*/
	IOC, /*Interrupt On Change. Available for INT0/1 only BUT NOT INT2*/
    FALLING_EDGE,
    RISING_EDGE
}EXTINT_EVENTSELECT_t;

typedef struct{
    EXINT_t INTNum;/*Use EXINT_t enum*/
    uint8 TriggerEvent;/*Use the EXTINT_EVENTSELECT_t enum*/
}EXTINT_Config_t;

/*******************************Needed Macros**********************************/
      /*Never change this Macros or the driver will operate improperly*/
/*******************************Needed Macros**********************************/

/*Interrupt status*/
#define INT_DISABLE            0
#define INT_ENABLE             1



/*********************************EXTt Interrupts APIs*************************/
/*To configure any pin of the RB<2:0> as EXTINT pin:
 * 1- Create an object of the struct EXTINT_Config_t.
 * 2- Use the MCAL_Interrupt_EXTIntStatus API to set the needed pin as input and configure it as you stated in the object.
 * 3- Set the priority of EXTINTx(Use MCAL_Interrupt_SetEXTIntPriority).
 */
/*Disable or Enable EXT INT and Set the configured triggering event(IOC, Falling, ....etc)*/
Std_ReturnType MCAL_EXT_Interrupt_EXTIntStatus(const EXTINT_Config_t Copy_EXTInt, const uint8 Copy_EXTIntStatus);
Std_ReturnType MCAL_EXT_Interrupt_ReadEXTIntFlag(const EXTINT_Config_t Copy_EXTInt, uint8 *Copy_FlagValue);
Std_ReturnType MCAL_EXT_Interrupt_ClearEXTIntFlag(const EXTINT_Config_t Copy_EXTInt);
/*SetCallBack APIs for EXTINTx */
Std_ReturnType MCAL_EXT_Interrupt_SetEXTINT0CallBack(void (*Copy_CallBackPtr)(void));
Std_ReturnType MCAL_EXT_Interrupt_SetEXTINT1CallBack(void (*Copy_CallBackPtr)(void));
Std_ReturnType MCAL_EXT_Interrupt_SetEXTINT2CallBack(void (*Copy_CallBackPtr)(void));


#endif	/* EXT_INTERRUPT_INTERFACE_H */

