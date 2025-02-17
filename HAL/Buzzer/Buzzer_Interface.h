/*
 * Buzzer_Interface.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Ali Mohamed
 */

#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"
#include "../MCAL/DIO/DIO_Interface.h"

typedef enum{
   Buzzer_OFF = 0,
   Buzzer_ON
}Buzzer_Status;

typedef struct{
	DIO_PORT_t PORT_ID    : 3;
	DIO_PIN_t Pin_Num     : 3;
	Buzzer_Status Buzzer_LastStatus : 1;/*ON or OFF*/
}Buzzer_Module_t;


Std_ReturnType HAL_Buzzer_BuzzerInit(Buzzer_Module_t *Copy_Buzzer);
Std_ReturnType HAL_Buzzer_BuzzerOn(Buzzer_Module_t *Copy_Buzzer);
Std_ReturnType HAL_Buzzer_BuzzerOff(Buzzer_Module_t *Copy_Buzzer);


#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
