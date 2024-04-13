/* 
 * File:   DIO_Private.h
 * Author: Ali Mohamed
 *
 * Created on March 1, 2024, 6:26 PM
 */

#ifndef DIO_PRIVATE_H
#define	DIO_PRIVATE_H

#include "D:\SDK\ATMEGA_Drivers\PLATFORM_TYPES.h"

/*********************************PORTA******************************************/

/*TRISA REGISTER : IT'S THE REGISTER RESPONSIBLE FOR DETERMINING PORT DIRECTION*/
 
typedef union {
    struct{
        uint8 DDRA_BIT0 : 1;
        uint8 DDRA_BIT1 : 1;
        uint8 DDRA_BIT2 : 1;
        uint8 DDRA_BIT3 : 1;
        uint8 DDRA_BIT4 : 1;
        uint8 DDRA_BIT5 : 1;
        uint8 DDRA_BIT6 : 1;
        uint8 DDRA_BIT7 : 1;
    };
    uint8 DDRA_REGISTER;
}DDRA_t;

#define DDRA_REG (*((volatile DDRA_t *)0x3A))

/*LATA REGISTER : IT'S THE REGISTER RESPONSIBLE FOR PIN VALUE @OUTPUT STATE****/

typedef union {
    struct{
        uint8 PORTA_BIT0 : 1;
        uint8 PORTA_BIT1 : 1;
        uint8 PORTA_BIT2 : 1;
        uint8 PORTA_BIT3 : 1;
        uint8 PORTA_BIT4 : 1;
        uint8 PORTA_BIT5 : 1;
        uint8 PORTA_BIT6 : 1;
        uint8 PORTA_BIT7 : 1;        
    };
    uint8 PORTA_REGISTER;
}PORTA_t;

#define PORTA_REG (*((volatile PORTA_t *)0x3B))

/*PORTA REGISTER : IT'S THE REGISTER WHICH CONTAINS THE PIN VALUE @INPUT STATE*/

typedef union {
    struct{
        uint8 PINA_BIT0 : 1;
        uint8 PINA_BIT1 : 1;
        uint8 PINA_BIT2 : 1;
        uint8 PINA_BIT3 : 1;
        uint8 PINA_BIT4 : 1;
        uint8 PINA_BIT5 : 1;
        uint8 PINA_BIT6 : 1;
        uint8 PINA_BIT7 : 1;
    };
    uint8 PINA_REGISTER;
}PINA_t;

#define PINA_REG (*((volatile PINA_t *)0x39))


/*********************************PORTB******************************************/

/*TRISB REGISTER : IT'S THE REGISTER RESPONSIBLE FOR DETERMINING PORT DIRECTION*/

typedef union {
    struct{
        uint8 DDRB_BIT0 : 1;
        uint8 DDRB_BIT1 : 1;
        uint8 DDRB_BIT2 : 1;
        uint8 DDRB_BIT3 : 1;
        uint8 DDRB_BIT4 : 1;
        uint8 DDRB_BIT5 : 1;
        uint8 DDRB_BIT6 : 1;
        uint8 DDRB_BIT7 : 1;
    };
    uint8 DDRB_REGISTER;
}DDRB_t;

#define DDRB_REG (*((volatile DDRB_t *)0x37))

/*LATB REGISTER : IT'S THE REGISTER RESPONSIBLE FOR PIN VALUE @OUTPUT STATE****/

typedef union {
    struct{
        uint8 PORTB_BIT0 : 1;
        uint8 PORTB_BIT1 : 1;
        uint8 PORTB_BIT2 : 1;
        uint8 PORTB_BIT3 : 1;
        uint8 PORTB_BIT4 : 1;
        uint8 PORTB_BIT5 : 1;
        uint8 PORTB_BIT6 : 1;
        uint8 PORTB_BIT7 : 1;        
    };
    uint8 PORTB_REGISTER;
}PORTB_t;

#define PORTB_REG (*((volatile PORTB_t *)0x38))

/*PORTB REGISTER : IT'S THE REGISTER WHICH CONTAINS THE PIN VALUE @INPUT STATE*/

typedef union {
    struct{
        uint8 PINB_BIT0 : 1;
        uint8 PINB_BIT1 : 1;
        uint8 PINB_BIT2 : 1;
        uint8 PINB_BIT3 : 1;
        uint8 PINB_BIT4 : 1;
        uint8 PINB_BIT5 : 1;
        uint8 PINB_BIT6 : 1;
        uint8 PINB_BIT7 : 1;
    };
    uint8 PINB_REGISTER;
}PINB_t;

#define PINB_REG (*((volatile PINB_t *)0x36))

/*********************************PORTC******************************************/

/*TRISC REGISTER : IT'S THE REGISTER RESPONSIBLE FOR DETERMINING PORT DIRECTION*/

typedef union {
    struct{
        uint8 DDRC_BIT0 : 1;
        uint8 DDRC_BIT1 : 1;
        uint8 DDRC_BIT2 : 1;
        uint8 DDRC_BIT3 : 1;
        uint8 DDRC_BIT4 : 1;
        uint8 DDRC_BIT5 : 1;
        uint8 DDRC_BIT6 : 1;
        uint8 DDRC_BIT7 : 1;
    };
    uint8 DDRC_REGISTER;
}DDRC_t;

#define DDRC_REG (*((volatile DDRC_t *)0x34))

/*LATC REGISTER : IT'S THE REGISTER RESPONSIBLE FOR PIN VALUE @OUTPUT STATE****/

typedef union {
    struct{
        uint8 PORTC_BIT0 : 1;
        uint8 PORTC_BIT1 : 1;
        uint8 PORTC_BIT2 : 1;
        uint8 PORTC_BIT3 : 1;
        uint8 PORTC_BIT4 : 1;
        uint8 PORTC_BIT5 : 1;
        uint8 PORTC_BIT6 : 1;
        uint8 PORTC_BIT7 : 1;        
    };
    uint8 PORTC_REGISTER;
}PORTC_t;

#define PORTC_REG (*((volatile PORTC_t *)0x35))

/*PORTC REGISTER : IT'S THE REGISTER WHICH CONTAINS THE PIN VALUE @INPUT STATE*/

typedef union {
    struct{
        uint8 PINC_BIT0 : 1;
        uint8 PINC_BIT1 : 1;
        uint8 PINC_BIT2 : 1;
        uint8 PINC_BIT3 : 1;
        uint8 PINC_BIT4 : 1;
        uint8 PINC_BIT5 : 1;
        uint8 PINC_BIT6 : 1;
        uint8 PINC_BIT7 : 1;
    };
    uint8 PINC_REGISTER;
}PINC_t;

#define PINC_REG (*((volatile PINC_t *)0x33))

/*********************************PORTD******************************************/

/*TRISD REGISTER : IT'S THE REGISTER RESPONSIBLE FOR DETERMINING PORT DIRECTION*/

typedef union {
    struct{
        uint8 DDRD_BIT0 : 1;
        uint8 DDRD_BIT1 : 1;
        uint8 DDRD_BIT2 : 1;
        uint8 DDRD_BIT3 : 1;
        uint8 DDRD_BIT4 : 1;
        uint8 DDRD_BIT5 : 1;
        uint8 DDRD_BIT6 : 1;
        uint8 DDRD_BIT7 : 1;
    };
    uint8 DDRD_REGISTER;
}DDRD_t;

#define DDRD_REG (*((volatile DDRD_t *)0x31))

/*LATD REGISTER : IT'S THE REGISTER RESPONSIBLE FOR PIN VALUE @OUTPUT STATE****/

typedef union {
    struct{
        uint8 PORTD_BIT0 : 1;
        uint8 PORTD_BIT1 : 1;
        uint8 PORTD_BIT2 : 1;
        uint8 PORTD_BIT3 : 1;
        uint8 PORTD_BIT4 : 1;
        uint8 PORTD_BIT5 : 1;
        uint8 PORTD_BIT6 : 1;
        uint8 PORTD_BIT7 : 1;        
    };
    uint8 PORTD_REGISTER;
}PORTD_t;

#define PORTD_REG (*((volatile PORTD_t *)0x32))

/*PORTD REGISTER : IT'S THE REGISTER WHICH CONTAINS THE PIN VALUE @INPUT STATE*/

typedef union {
    struct{
        uint8 PIND_BIT0 : 1;
        uint8 PIND_BIT1 : 1;
        uint8 PIND_BIT2 : 1;
        uint8 PIND_BIT3 : 1;
        uint8 PIND_BIT4 : 1;
        uint8 PIND_BIT5 : 1;
        uint8 PIND_BIT6 : 1;
        uint8 PIND_BIT7 : 1;
    };
    uint8 PIND_REGISTER;
}PIND_t;

#define PIND_REG (*((volatile PIND_t *)0x30))

/**< SFIOR_REG is the register containing the bit(PUD_BIT) which en/disable the Internal Pull-Up option*/

#define SFIOR_REG (*((volatile uint8 *)0x50))
#define PUB_BIT   0x2

#endif	/* DIO_PRIVATE_H */

