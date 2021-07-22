/*
 * Button.c
 *
 * Created: 5/28/2021 4:44:31 PM
 *  Author: ahmed
 */ 

#include "Button.h"
#define F_CPU 16000000
#include <util/delay.h>

Uint8 BUTTON0_GetPinVal(void)
{
	Uint8 val = 0;
	val = DIO_GetPinVal(BUTTON0_PORT, BUTTON0_PIN);
	while(DIO_GetPinVal(BUTTON0_PORT, BUTTON0_PIN));
	_delay_ms(20);
	return val;	
}
Uint8 BUTTON1_GetPinVal(void)
{
	Uint8 val = 0;
	val = DIO_GetPinVal(BUTTON1_PORT, BUTTON1_PIN);
	while(DIO_GetPinVal(BUTTON1_PORT, BUTTON1_PIN));
	_delay_ms(20);
	return val;	
}
Uint8 BUTTON2_GetPinVal(void)
{
	Uint8 val = 0;
	val = DIO_GetPinVal(BUTTON2_PORT, BUTTON2_PIN);
	while(DIO_GetPinVal(BUTTON2_PORT, BUTTON2_PIN));
	_delay_ms(20);
	return val;	
}

