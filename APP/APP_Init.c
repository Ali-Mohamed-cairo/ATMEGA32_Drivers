/*
 * APP_Init.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Ali Mohamed
 */

#include "APP_Init.h"


KeyPad_t key = {
	.KeyPad_Rows_Pins[0] = {
		.Pin_Num = DIO_PIN0,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Rows_Pins[1] = {
		.Pin_Num = DIO_PIN1,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Rows_Pins[2] = {
		.Pin_Num = DIO_PIN2,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Rows_Pins[3] = {
		.Pin_Num = DIO_PIN3,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Cols_Pins[0] = {
		.Pin_Num = DIO_PIN4,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Cols_Pins[1] = {
		.Pin_Num = DIO_PIN5,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Cols_Pins[2] = {
		.Pin_Num = DIO_PIN6,
		.PORT_ID = DIO_PORTB
	},
	.KeyPad_Cols_Pins[3] = {
		.Pin_Num = DIO_PIN7,
		.PORT_ID = DIO_PORTB
	}
};


LED_t led0 = {
	.PORT_ID = LED_PORTC,
	.Pin_Num = LED_PIN2,
	.LED_Status = LED_OFF
};
LED_t led1 = {
	.PORT_ID = LED_PORTC,
	.Pin_Num = LED_PIN7,
	.LED_Status = LED_OFF
};
LED_t led2 = {
	.PORT_ID = LED_PORTD,
	.Pin_Num = LED_PIN3,
	.LED_Status = LED_OFF
};

PushBtn_t Btn = {
	.PORT_ID = Btn_PORTD,
	.Pin_Num = Btn_PIN6,
	.Connection_Meth = PULL_DOWN_Connection,
	.Last_Status = Btn_D_Released
};

Std_ReturnType APP_APPInit(void)
{
	Std_ReturnType Local_ErrorState = E_NOT_OK;
	HAL_LED_LEDConfig(&led0);
	HAL_LED_LEDConfig(&led1);
	HAL_LED_LEDConfig(&led2);
	HAL_Push_Button_BtnConfig(&Btn);
	HAL_KeyPad_KeyPadInit(&key);
	Local_ErrorState = E_OK;
	return Local_ErrorState;
}


