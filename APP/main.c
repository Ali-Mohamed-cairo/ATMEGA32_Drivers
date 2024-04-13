


#include "APP_Init.h"

uint8 Global_KeyRead = '\0';
uint8 Global_BtnRead = '\0';
Std_ReturnType ReturnStatus = E_NOT_OK;

int main()
{
	APP_APPInit();

    /*1 -  ReturnStatus = MCAL_DIO_SetPinDirection(&Btn_1);
    ReturnStatus = MCAL_DIO_InitializePinOutput(&LED_1);
    ReturnStatus = MCAL_DIO_InitializePinOutput(&LED_2);
    ReturnStatus = MCAL_DIO_InitializePinOutput(&LED_3);  */

    /*2 -  ReturnStatus = MCAL_DIO_SetPortDirection(&portd);
    ReturnStatus = MCAL_DIO_SetPortDirection(&portc);
    ReturnStatus = MCAL_DIO_SetPortValue(&portc, portc.Port_Value);*/


    while(1)
    {
    	while('\0' == Global_BtnRead && '\0' == Global_KeyRead)
    	{
    		HAL_KeyPad_KeyPadReadCharacter(&key, &Global_KeyRead);
    		HAL_Push_Button_ReadBtn(&Btn, &Global_BtnRead);
    	}

    	if(Global_BtnRead != '\0')
    	{
    		HAL_LED_LEDBlink(&led0);
    		HAL_LED_LEDBlink(&led1);
    		HAL_LED_LEDBlink(&led2);
    	}
    	else if(Global_KeyRead != '\0')
    	{
    		if(Global_KeyRead == '1')
    		{
    			HAL_LED_LEDBlink(&led0);
    		}

    		else if(Global_KeyRead == '5')
    		{
    			HAL_LED_LEDBlink(&led1);
    		}

    		else if(Global_KeyRead == '9')
    		{
    			 HAL_LED_LEDBlink(&led2);
    		}
    	}
    	Global_KeyRead = '\0';
    	Global_BtnRead = '\0';
        /*2 -  while(Global_BtnRead == 0x00)
        {
            ReturnStatus = MCAL_DIO_ReadPortValue(&portd, &Global_BtnRead);
        }
        Global_BtnRead = E_OK;
        ReturnStatus = MCAL_DIO_TogglePortValue(&portc);*/

        /*1 -  while(Global_BtnRead == E_OK)
        {
            ReturnStatus = MCAL_DIO_ReadPinValue(&Btn_1, &Global_BtnRead);
        }
        Global_BtnRead = E_OK;
        ReturnStatus = MCAL_DIO_SetPinValue(&LED_1, DIO_HIGH);
        while(Global_BtnRead == E_OK)
        {
            ReturnStatus = MCAL_DIO_ReadPinValue(&Btn_1, &Global_BtnRead);
        }
        Global_BtnRead = E_OK;
        ReturnStatus = MCAL_DIO_SetPinValue(&LED_2, DIO_HIGH);
        while(Global_BtnRead == E_OK)
        {
            ReturnStatus = MCAL_DIO_ReadPinValue(&Btn_1, &Global_BtnRead);
        }
        Global_BtnRead = E_OK;
        ReturnStatus = MCAL_DIO_SetPinValue(&LED_3, DIO_HIGH);
        while(Global_BtnRead == E_OK)
        {
            ReturnStatus = MCAL_DIO_ReadPinValue(&Btn_1, &Global_BtnRead);
        }
        Global_BtnRead = E_OK;
        ReturnStatus = MCAL_DIO_SetPinValue(&LED_1, DIO_LOW);
        ReturnStatus = MCAL_DIO_SetPinValue(&LED_2, DIO_LOW);
        ReturnStatus = MCAL_DIO_SetPinValue(&LED_3, DIO_LOW);*/
    }

    return 0;
}
