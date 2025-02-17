


#include "APP_Init.h"
#include "ISRs/ISRs.h"

SSD_Module_t SSD_an = {
		.SSD_Type = COMMON_ANODE,
		.Decoder_Type = SOFTWARE_DEC,
        .SSD_Common = {.PORT_ID = DIO_PORTA, .Pin_Num = DIO_PIN1, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin0_A = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN0, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin1_B = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN1, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin2_C = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN2, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin3_D = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN3, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin4_E = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN4, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin5_F = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN5, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin6_G = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN6, .Pin_Direction = DIO_PIN_OUTPUT},
        .ValueToBeDisplayed = 4
};

SSD_Module_t SSD_Cath = {
		.SSD_Type = COMMON_CATHODE,
		.Decoder_Type = HEX_DEC,
        .SSD_Common = {.PORT_ID = DIO_PORTB, .Pin_Num = DIO_PIN1, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin0_A = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN0, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin1_B = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN1, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin2_C = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN2, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin3_D = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN3, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin4_E = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN4, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin5_F = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN5, .Pin_Direction = DIO_PIN_OUTPUT},
		.SSD_Pin6_G = {.PORT_ID = DIO_PORTC, .Pin_Num = DIO_PIN6, .Pin_Direction = DIO_PIN_OUTPUT},
        .ValueToBeDisplayed = 3
};

int main()
{
	HAL_SSD_SSDInit(&SSD_an, MC_Generate_NUM);
	HAL_SSD_SSDDisplayNumWithSoftwareDecoder(&SSD_an);
	while(1)
	{

	}
	return 0;
}
