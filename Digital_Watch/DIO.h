/*
 * DIO.h
 *
 * Created: 5/26/2021 12:44:58 PM
 *  Author: ahmed
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "std.h"
#include "MC_Selector.h"
#include "Bit_Math.h"
/*Port Selection*/
#define DIO_PORTA        0
#define DIO_PORTB        1
#define DIO_PORTC        2
#define DIO_PORTD        3
/*Pin Selection*/
#define DIO_PIN_0        0
#define DIO_PIN_1        1
#define DIO_PIN_2        2
#define DIO_PIN_3        3
#define DIO_PIN_4        4
#define DIO_PIN_5        5
#define DIO_PIN_6        6
#define DIO_PIN_7        7
#define DIO_ALL_PINs     8
/*Direction Selection*/
#define DIO_PIN_IN       0x00
#define DIO_PIN_OUT      0xff
/*Output Value Selection*/
#define DIO_PIN_OFF      0x00
#define DIO_PIN_ON       0xff

void DIO_SetPinDir(Uint8 port, Uint8 pin, Uint8 dir);

void DIO_SetPinVal(Uint8 port, Uint8 pin, Uint8 val);

void DIO_TogglePin(Uint8 port, Uint8 pin);

Uint8 DIO_GetPinVal(Uint8 port, Uint8 pin);

void DIO_SetPullup(Uint8 port, Uint8 pin);


#endif /* DIO_H_ */