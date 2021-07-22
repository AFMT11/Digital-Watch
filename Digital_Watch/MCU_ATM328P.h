/*
 * MCU_ATM328P.h
 *
 * Created: 6/15/2021 12:25:21 AM
 *  Author: ahmed
 */ 


#ifndef MCU_ATM328P_H_
#define MCU_ATM328P_H_

/***************************************** DIO ********************************************/
#define PORTA    (*(volatile char*)(0x00))
#define DDRA     (*(volatile char*)(0x00))
#define PINA     (*(volatile char*)(0x00))

#define PORTB    (*(volatile char*)(0x25))
#define DDRB     (*(volatile char*)(0x24))
#define PINB     (*(volatile char*)(0x23))

#define PORTC    (*(volatile char*)(0x28))
#define DDRC     (*(volatile char*)(0x27))
#define PINC     (*(volatile char*)(0x26))

#define PORTD    (*(volatile char*)(0x2B))
#define DDRD     (*(volatile char*)(0x2A))
#define PIND     (*(volatile char*)(0x29))
/***************************************** EXT INT ********************************************/
#define  SREG    (*(volatile char*)(0x5F))
#define  GICR    (*(volatile char*)(0x5B))
#define  GIFR    (*(volatile char*)(0x5A))
#define  MCUCR   (*(volatile char*)(0x55))
#define  MCUCSR  (*(volatile char*)(0x54))




#endif /* MCU_ATM328P_H_ */