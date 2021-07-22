/*
 * Buzz.c
 *
 * Created: 7/18/2021 9:19:04 PM
 *  Author: ahmed
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include "Buzz.h"

void BUZZ_ON(void)
{
	DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_ON);
}
void BUZZ_OFF(void)
{
	DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_OFF);
}

void Buzz_Tone0(void)
{
	Uint8 i;
	for (i = 0; i < 4; i++)
	{
		DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_ON);
		_delay_ms(50);
		DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_OFF);
		_delay_ms(100);
	}
}
void Buzz_Tone1(void)
{
		DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_ON);
		_delay_ms(5);
		DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_OFF);
}
void Buzz_Tone2(void)
{
	Uint8 i;
	for (i = 0; i < 2; i++)
	{
		DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_ON);
		_delay_ms(100);
		DIO_SetPinVal(Buzz_Port, Buzz_Pin, DIO_PIN_OFF);
		_delay_ms(50);
	}
}
