/*
 * Keypad_CFG.h
 *
 * Created: 7/17/2021 5:57:22 PM
 *  Author: ahmed
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "DIO.h"

/*keypad (col/row) port selection*/
#define Keypad_Col_Port    DIO_PORTC
#define Keypad_Row_Port    DIO_PORTC

/*keypad column pins selection*/
#define Keypad_Col_0       DIO_PIN_0
#define Keypad_Col_1       DIO_PIN_1
#define Keypad_Col_2       DIO_PIN_2
#define Keypad_Col_3       DIO_PIN_3

/*keypad row pins selection*/
#define Keypad_Row_0       DIO_PIN_4
#define Keypad_Row_1       DIO_PIN_5
#define Keypad_Row_2       DIO_PIN_6
#define Keypad_Row_3       DIO_PIN_7

#define Keypad_Col_start   0
#define Keypad_Col_end     3

#define Keypad_Row_start   4
#define Keypad_Row_end     7

#endif /* KEYPAD_CFG_H_ */