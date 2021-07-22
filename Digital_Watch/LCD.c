/*
 * LCD.c
 *
 * Created: 6/7/2021 11:58:33 AM
 *  Author: ahmed
 */ 
#include "LCD.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <math.h>


void LCD_INIT(void)
{
	/*Set direction of command pins (RS, RW, E)*/
	DIO_SetPinDir(LCD_4_BIT_CMD_PORT, RS_PIN, DIO_PIN_OUT);
	DIO_SetPinDir(LCD_4_BIT_CMD_PORT, RW_PIN, DIO_PIN_OUT);
	DIO_SetPinDir(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OUT);
	/*Set direction of data pins*/
	DIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN4, DIO_PIN_OUT);
	DIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN5, DIO_PIN_OUT);
	DIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN6, DIO_PIN_OUT);
	DIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN7, DIO_PIN_OUT);
	_delay_ms(100);
	/*choose 4-bit mode*/
	LCD_WriteCMD(0x33);
	LCD_WriteCMD(0x32);
	LCD_WriteCMD(LCD_4_Bit_Mode);
	///////////////////////////
	LCD_WriteCMD(Clear_Display_Screen);
	LCD_WriteCMD(Return_Home);
	LCD_WriteCMD(Shift_cursor_Right);
	LCD_WriteCMD(Display_ON_Cursor_OFF);
	
}
void LCD_WriteCMD(Uint8 cmd)
{
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, RS_PIN, DIO_PIN_OFF);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, RW_PIN, DIO_PIN_OFF);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OFF);
	
	LCD_4_BIT_BUS = (cmd & 0xF0) | (LCD_4_BIT_BUS & 0x0F);
	
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_ON);
	_delay_ms(1);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OFF);
	
	LCD_4_BIT_BUS = (cmd << 4) | (LCD_4_BIT_BUS & 0x0F);
	
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_ON);
	_delay_ms(1);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OFF);	
	
	_delay_ms(5);
}
void LCD_WriteCHAR(Uint8 chr)
{
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, RS_PIN, DIO_PIN_ON);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, RW_PIN, DIO_PIN_OFF);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OFF);
	
	LCD_4_BIT_BUS = (chr & 0xF0) | (LCD_4_BIT_BUS & 0x0F);
	
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_ON);
	_delay_ms(1);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OFF);
	
	LCD_4_BIT_BUS = (chr << 4) | (LCD_4_BIT_BUS & 0x0F);
	
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_ON);
	_delay_ms(1);
	DIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, DIO_PIN_OFF);
	
	//_delay_ms(5);	
}
void LCD_WriteSTRING(Uint8 * str)
{
	Uint8 counter = 0;
	while (str[counter] != '\0')
	{
		LCD_WriteCHAR(str[counter]);
		counter++;
	}
	
}
void LCD_WriteINTEGER(Uint32 integer)
{
	Uint32 Revers_num = 0;
	Uint8 displayed_num = 0;
	Uint32 multiplier = 1, i = 0;
	if(integer == 0)
	{
		LCD_WriteCHAR('0');
	}
	else if(integer < 0)
	{
		LCD_WriteCHAR('-');
		integer *= -1;
	}
	
	while (integer != 0)
	{
		Revers_num = (Revers_num * 10) + integer % 10;
		if (Revers_num == 0)	
		multiplier *= 10;
		integer /= 10;
	}	
	while (Revers_num != i)
	{
		displayed_num = Revers_num % 10;
		LCD_WriteCHAR(displayed_num + 48);
		Revers_num/=10;
		if (Revers_num == 0 && multiplier >= 10)
		{
			i = 1;
			Revers_num = multiplier;
		}	
	}
}
void LCD_WriteDECIMAL(f32 decimal)
{
   int val,i;
   val = (int) decimal;
   LCD_WriteINTEGER(val);
   LCD_WriteCHAR('.');
   decimal -= val;
   for (i = 0; i < 5; i++)
   {
	   decimal *=10;
	   val = (int)decimal;
	   LCD_WriteINTEGER(val);
	   decimal -=val;
   }	
}
void LCD_GoTo(Uint8 row, Uint8 col)
{
	Uint8 arr[2] = {Cursor_Begin_1st_Line, Cursor_Begin_2st_Line};
	LCD_WriteCMD(arr[row] + col);
}
void LCD_Clear(void)
{
	LCD_WriteCMD(Clear_Display_Screen);
}
