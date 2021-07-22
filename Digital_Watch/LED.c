/*
 * LED.c
 *
 * Created: 6/12/2021 9:05:00 PM
 *  Author: ahmed
 */

#include "LED.h" 

void LED0_ON(void)
{
	DIO_SetPinVal(LED0_PORT, LED0_PIN, DIO_PIN_ON);
}
void LED0_OFF(void)
{
	DIO_SetPinVal(LED0_PORT, LED0_PIN, DIO_PIN_OFF);
}
void LED0_Toggle(void)
{
	DIO_TogglePin(LED0_PORT, LED0_PIN);
}

void LED1_ON(void)
{
	DIO_SetPinVal(LED1_PORT, LED1_PIN, DIO_PIN_ON);
}
void LED1_OFF(void)
{
	DIO_SetPinVal(LED1_PORT, LED1_PIN, DIO_PIN_OFF);
}
void LED1_Toggle(void)
{
	DIO_TogglePin(LED1_PORT, LED1_PIN);
}

void LED2_ON(void)
{
	DIO_SetPinVal(LED2_PORT, LED2_PIN, DIO_PIN_ON);
}
void LED2_OFF(void)
{
	DIO_SetPinVal(LED2_PORT, LED2_PIN, DIO_PIN_OFF);
}
void LED2_Toggle(void)
{
	DIO_TogglePin(LED2_PORT, LED2_PIN);
}