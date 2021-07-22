/*
 * Timers.h
 *
 * Created: 7/10/2021 7:45:16 PM
 *  Author: ahmed
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "Timer_CFG.h"

/*Timer0 Modes*/
#define NORMAL_MODE             0
#define PWM_MODE                1
#define CTC_MODE                2
#define FAST_PWM_MODE           3

/*Timer0 Clocks*/
#define T0_NO_CLOCK                0
#define T0_PURE_CLOCK              1
#define T0_CLOCK_8                 2
#define T0_CLOCK_64                3
#define T0_CLOCK_256               4
#define T0_CLOCK_1024              5

/*Timer1 Clocks*/
#define T1_NO_CLOCK                0
#define T1_PURE_CLOCK              1
#define T1_CLOCK_8                 2
#define T1_CLOCK_64                3
#define T1_CLOCK_256               4
#define T1_CLOCK_1024              5

/*Timer2 Clocks*/
#define T2_NO_CLOCK                0
#define T2_PURE_CLOCK              1
#define T2_CLOCK_8                 2
#define T2_CLOCK_32                3
#define T2_CLOCK_64                4
#define T2_CLOCK_128               5
#define T2_CLOCK_256               6
#define T2_CLOCK_1024              7

typedef struct
{
	int arr[6];
	int top;
}Inv_Stack;

typedef struct
{
	int arr[12];
	int top;
}Stack;

/*Inv-Stack of Timer 0*/
void Inv_Stack_INIT(Inv_Stack *p);
void Inv_Stack_PUSH(Inv_Stack *p, int data);
void Inv_Stack_Remove(Inv_Stack *p);

/*Stack of Timer 1*/
void Stack_INIT(Stack *p);
void Stack_PUSH(Stack *p, int data);
void Stack_Remove(Stack *p);

/*Timer0 Functions*/
void TIMER0_INIT(void);
void TIMER0_Start(void);
void TIMER0_Stop(void);
void TIMER0_SetDelay(Uint32 delay);

/*Timer1 Functions*/
void TIMER1_INIT(void);
void TIMER1_Start(void);
void TIMER1_Stop(void);
void TIMER1_SetDelay(Uint32 delay);

/*Timer2 Functions*/
void TIMER2_INIT(void);
void TIMER2_Start(void);
void TIMER2_Stop(void);
void TIMER2_SetDelay(Uint32 delay);


#endif /* TIMERS_H_ */