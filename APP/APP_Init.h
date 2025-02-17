/*
 * APP_Init.h
 *
 *  Created on: Apr 13, 2024
 *      Author: Ali Mohamed
 */

#ifndef APP_APP_INIT_H_
#define APP_APP_INIT_H_


#include <util/delay.h>

#include "../PLATFORM_TYPES.h"
#include "../BIT_MATH.h"


#include "../DIO/DIO_Interface.h"
#include "../LED/LED_Interface.h"
#include "../Push_Button/Push_Button_Interface.h"
#include "../KeyPad/KeyPad_Interface.h"
#include "../GIE/GIE_Interface.h"
#include "../MCAL/EXT_Interrupt/EXT_Interrupt_Interface.h"
#include "../MCAL/UART/UART_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/SSD/SSD_Interface.h"
#include "../HAL/POT/POT_Interface.h"
#include "../HAL/Buzzer/Buzzer_Interface.h"



extern KeyPad_t key;
extern LED_t led0;
extern LED_t led1;
extern LED_t led2;
extern PushBtn_t Btn;


Std_ReturnType APP_APPInit(void);

#endif /* APP_APP_INIT_H_ */
