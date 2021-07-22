/*
 * Keypad.c
 *
 * Created: 7/17/2021 5:56:33 PM
 *  Author: ahmed
 */ 

#include "Keypad.h"

	/*keypad Array*/
Uint8 arr[4][4] = {
					{'1', '2', '3', 'A'},
					{'4', '5', '6', 'B'},
					{'7', '8', '9', 'C'},
					{'*', '0', '#', 'D'}
				};

void Keypad_INIT(void)
{
	/*column pins direction*/
	DIO_SetPinDir(Keypad_Col_Port, Keypad_Col_0, DIO_PIN_OUT);
	DIO_SetPinDir(Keypad_Col_Port, Keypad_Col_1, DIO_PIN_OUT);
	DIO_SetPinDir(Keypad_Col_Port, Keypad_Col_2, DIO_PIN_OUT);
	DIO_SetPinDir(Keypad_Col_Port, Keypad_Col_3, DIO_PIN_OUT);
	
	/*row pins direction*/
	DIO_SetPinDir(Keypad_Row_Port, Keypad_Row_0, DIO_PIN_IN);
	DIO_SetPinDir(Keypad_Row_Port, Keypad_Row_1, DIO_PIN_IN);
	DIO_SetPinDir(Keypad_Row_Port, Keypad_Row_2, DIO_PIN_IN);
	DIO_SetPinDir(Keypad_Row_Port, Keypad_Row_3, DIO_PIN_IN);
	
	/*column pins value*/
	DIO_SetPinVal(Keypad_Col_Port, Keypad_Col_0, DIO_PIN_ON);
	DIO_SetPinVal(Keypad_Col_Port, Keypad_Col_1, DIO_PIN_ON);
	DIO_SetPinVal(Keypad_Col_Port, Keypad_Col_2, DIO_PIN_ON);
	DIO_SetPinVal(Keypad_Col_Port, Keypad_Col_3, DIO_PIN_ON);
	
	/*row pins pull-up setup*/
	DIO_SetPullup(Keypad_Row_Port, Keypad_Row_0);
	DIO_SetPullup(Keypad_Row_Port, Keypad_Row_1);
	DIO_SetPullup(Keypad_Row_Port, Keypad_Row_2);
	DIO_SetPullup(Keypad_Row_Port, Keypad_Row_3);
}

Uint8 Keypad_GetVal(void)
{
	Uint8 i,j, val = 0;
	
	for (i = Keypad_Col_start; i <= Keypad_Col_end; i++)
	{
		DIO_SetPinVal(Keypad_Col_Port, i, DIO_PIN_OFF);
		for (j = Keypad_Row_start; j <= Keypad_Row_end; j++)
		{
			if (DIO_GetPinVal(Keypad_Row_Port, j) == 0)
			{
				while(DIO_GetPinVal(Keypad_Row_Port, j) == 0);
				val = arr[j - Keypad_Row_start][i - Keypad_Col_start];
			}
		}
		DIO_SetPinVal(Keypad_Col_Port, i, DIO_PIN_ON);
	}
	return val;
}
