/*
 * LCD_CFG.h
 *
 * Created: 6/7/2021 11:59:10 AM
 *  Author: ahmed
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "DIO.h"

#define LCD_8_BIT_CMD_PORT           DIO_PORTB
#define LCD_8_BIT_DATA_PORT          DIO_PORTA
#define LCD_8_BIT_BUS                PORTA

#define LCD_4_BIT_CMD_PORT           DIO_PORTB
#define LCD_4_BIT_DATA_PORT          DIO_PORTA
#define LCD_4_BIT_BUS                PORTA

#define RS_PIN                       DIO_PIN_1
#define RW_PIN                       DIO_PIN_2
#define E_PIN                        DIO_PIN_3

#define LCD_PIN0                     DIO_PIN_0
#define LCD_PIN1                     DIO_PIN_1
#define LCD_PIN2                     DIO_PIN_2
#define LCD_PIN3                     DIO_PIN_3
#define LCD_PIN4                     DIO_PIN_4
#define LCD_PIN5                     DIO_PIN_5
#define LCD_PIN6                     DIO_PIN_6
#define LCD_PIN7                     DIO_PIN_7

#endif /* LCD_CFG_H_ */