/*
 * DIO.c
 *
 * Created: 5/26/2021 12:45:12 PM
 *  Author: ahmed
 */
#include "DIO.h"

void DIO_SetPinDir(Uint8 port, Uint8 pin, Uint8 dir)
{
	switch (dir)
	{
		case DIO_PIN_IN:
		if (pin >=0 && pin <=7)
		{
			switch (port)
			{
				case DIO_PORTA:
				Clear_Bit(DDRA, pin);
				break;
				case DIO_PORTB:
				Clear_Bit(DDRB, pin);
				break;
				case DIO_PORTC:
				Clear_Bit(DDRC, pin);
				break;
				case DIO_PORTD:
				Clear_Bit(DDRD, pin);
				break;
				default:   //MISRA C rules
				break;																
			}
		}
		else
		{
			switch (port)
			{
				case DIO_PORTA:
				DDRA = dir;
				break;
				case DIO_PORTB:
				DDRB = dir;
				break;
				case DIO_PORTC:
				DDRC = dir;
				break;
				case DIO_PORTD:
				DDRD = dir;
				break;
				default:   //MISRA C rules
				break;																
			}
		}
		break;
		case DIO_PIN_OUT:
		if (pin >=0 && pin <=7)
		{
			switch (port)
			{
				case DIO_PORTA:
				Set_Bit(DDRA, pin);
				break;
				case DIO_PORTB:
				Set_Bit(DDRB, pin);
				break;
				case DIO_PORTC:
				Set_Bit(DDRC, pin);
				break;
				case DIO_PORTD:
				Set_Bit(DDRD, pin);
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		else
		{
			switch (port)
			{
				case DIO_PORTA:
				DDRA = dir;
				break;
				case DIO_PORTB:
				DDRB = dir;
				break;
				case DIO_PORTC:
				DDRC = dir;
				break;
				case DIO_PORTD:
				DDRD = dir;
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		break;		
		default:   //MISRA C rules
		break;		
	}
}
void DIO_SetPinVal(Uint8 port, Uint8 pin, Uint8 val)
{
	switch (val)
	{
		case DIO_PIN_OFF:
		if (pin >=0 && pin <=7)
		{
			DIO_SetPinDir(port, pin, DIO_PIN_OUT);
			switch (port)
			{
				case DIO_PORTA:
				Clear_Bit(PORTA, pin);
				break;
				case DIO_PORTB:
				Clear_Bit(PORTB, pin);
				break;
				case DIO_PORTC:
				Clear_Bit(PORTC, pin);
				break;
				case DIO_PORTD:
				Clear_Bit(PORTD, pin);
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		else
		{
			DIO_SetPinDir(port, DIO_ALL_PINs, DIO_PIN_OUT);
			switch (port)
			{
				case DIO_PORTA:
				PORTA = val;
				break;
				case DIO_PORTB:
				PORTB = val;
				break;
				case DIO_PORTC:
				PORTC = val;
				break;
				case DIO_PORTD:
				PORTD = val;
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		break;
		case DIO_PIN_ON:
		if (pin >=0 && pin <=7)
		{
			DIO_SetPinDir(port, pin, DIO_PIN_OUT);
			switch (port)
			{
				case DIO_PORTA:
				Set_Bit(PORTA, pin);
				break;
				case DIO_PORTB:
				Set_Bit(PORTB, pin);
				break;
				case DIO_PORTC:
				Set_Bit(PORTC, pin);
				break;
				case DIO_PORTD:
				Set_Bit(PORTD, pin);
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		else
		{
			DIO_SetPinDir(port, DIO_ALL_PINs, DIO_PIN_OUT);
			switch (port)
			{
				case DIO_PORTA:
				PORTA = val;
				break;
				case DIO_PORTB:
				PORTB = val;
				break;
				case DIO_PORTC:
				PORTC = val;
				break;
				case DIO_PORTD:
				PORTD = val;
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		break;
		default:   //MISRA C rules
		break;		
	}	
}
void DIO_TogglePin(Uint8 port, Uint8 pin)
{
	if (pin >=0 && pin <=7)
	{
		DIO_SetPinDir(port, pin, DIO_PIN_OUT);
		switch (port)
		{
			case DIO_PORTA:
			Toggle_Bit(PORTA, pin);
			break;
			case DIO_PORTB:
			Toggle_Bit(PORTB, pin);
			break;
			case DIO_PORTC:
			Toggle_Bit(PORTC, pin);
			break;
			case DIO_PORTD:
			Toggle_Bit(PORTD, pin);
			break;	
			default:   //MISRA C rules
			break;											
		}
	}
	else
	{
		DIO_SetPinDir(port, DIO_ALL_PINs, DIO_PIN_OUT);
		switch (port)
		{
			case DIO_PORTA:
			PORTA ^= 0xff;
			break;
			case DIO_PORTB:
			PORTB ^= 0xff;
			break;
			case DIO_PORTC:
			PORTC ^= 0xff;
			break;
			case DIO_PORTD:
			PORTD ^= 0xff;
			break;		
			default:   //MISRA C rules
			break;										
		}	
	}
}
Uint8 DIO_GetPinVal(Uint8 port, Uint8 pin)
{
	Uint8 val = 0;
		if (pin >=0 && pin <=7)
		{
			DIO_SetPinDir(port, pin, DIO_PIN_IN);
			switch (port)
			{
				case DIO_PORTA:
				val = Get_Bit(PINA, pin);
				break;
				case DIO_PORTB:
				val = Get_Bit(PINB, pin);
				break;
				case DIO_PORTC:
				val = Get_Bit(PINC, pin);
				break;
				case DIO_PORTD:
				val = Get_Bit(PIND, pin);
				break;
				default:   //MISRA C rules
				break;				
			}
		}
		else
		{
			DIO_SetPinDir(port, DIO_ALL_PINs, DIO_PIN_IN);
			switch (port)
			{
				case DIO_PORTA:
				val = PINA;
				break;
				case DIO_PORTB:
				val = PINB;
				break;
				case DIO_PORTC:
				val = PINC;
				break;
				case DIO_PORTD:
				val = PIND;
				break;
				default:   //MISRA C rules
				break;				
			}
		}
	return val;
}
void DIO_SetPullup(Uint8 port, Uint8 pin)
{
		if (pin >=0 && pin <=7)
		{
			DIO_SetPinDir(port, pin, DIO_PIN_IN);
			switch (port)
			{
				case DIO_PORTA:
				Set_Bit(PORTA, pin);
				break;
				case DIO_PORTB:
				Set_Bit(PORTB, pin);
				break;
				case DIO_PORTC:
				Set_Bit(PORTC, pin);
				break;
				case DIO_PORTD:
				Set_Bit(PORTD, pin);
				break;
				default:   //MISRA C rules
				break;
			}
		}
		else
		{
			DIO_SetPinDir(port, DIO_ALL_PINs, DIO_PIN_IN);
			switch (port)
			{
				case DIO_PORTA:
				PORTA = 0xff;
				break;
				case DIO_PORTB:
				PORTB = 0xff;
				break;
				case DIO_PORTC:
				PORTC = 0xff;
				break;
				case DIO_PORTD:
				PORTD = 0xff;
				break;
				default:   //MISRA C rules
				break;				
			}
		}	
}
