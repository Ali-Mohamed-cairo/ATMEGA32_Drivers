/* 
 * File:   Push_Button_Interface.h
 * Author: Ali Mohamed
 *
 * Created on March 5, 2024, 11:05 AM
 */

#ifndef PUSH_BUTTON_INTERFACE_H
#define	PUSH_BUTTON_INTERFACE_H

/**********************************Includes************************************/

#include "../../Platform_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "Push_Button_Config.h"



/**********************************MACROS**************************************/

#define INITIAL_VALUE           6    /*Aimless random value*/
#define _XTAL_FREQ              16000000 //For delay function
#define PULL_DOWN_Connection      0
#define PULL_UP_Connection        1

/*********************************REQUIRED ENUMS*******************************/

typedef enum{
    Btn_PIN0 = 0,
    Btn_PIN1,
    Btn_PIN2,
    Btn_PIN3,
    Btn_PIN4,
    Btn_PIN5,
    Btn_PIN6,
    Btn_PIN7
}PushBtnPIN_t;

typedef enum{
    Btn_PORTA = 0,
    Btn_PORTB,
    Btn_PORTC,
    Btn_PORTD,
    Btn_PORTE
}PushBtnPORT_t;

typedef enum{
    Btn_D_Released = 0,       
    Btn_D_Pressed       
}Btn_Pull_Down_Status;

typedef enum{
    Btn_U_Pressed = 0,
    Btn_U_Released              
}Btn_Pull_Up_Status;

/*****************************Configuration structs****************************/

typedef struct{
    uint8 PORT_ID         : 3;
    uint8 Pin_Num         : 3;
    uint8 Connection_Meth : 1; /*PULL_UP_CONNECTION or PULL_DOWN_CONNECTION*/
    uint8 Last_Status     : 1; /*Btn_Pressed or Btn_Released*/
}PushBtn_t;

/*typedef struct{
    uint8 PORT_ID   : 3;
    uint8 Start_Pin : 1;
    uint8 End_Pin   : 1;
    uint8 Pattern_Value;
}LEDArray_t;
*/

/***********************************APIs***************************************/

Std_ReturnType HAL_Push_Button_BtnConfig(const PushBtn_t *Copy_Btn);
Std_ReturnType HAL_Push_Button_ReadBtn(PushBtn_t *Copy_Btn, uint8 *Copy_BtnStatus);


#endif	/* PUSH_BUTTON_INTERFACE_H */

