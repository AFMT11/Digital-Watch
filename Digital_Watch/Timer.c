/*
 * Timers.c
 *
 * Created: 7/10/2021 7:44:59 PM
 *  Author: Ahmed Atef
 */ 

#include "Timer.h"

#include <avr/interrupt.h>

/*Global Variables*/
//Timer_0
Uint32 T0_OVF_No = 1;        //Global number of overflows to be used in Timer.c, & also in ISR
Uint32 T0_Init_val;          //Global number of the initial value of the first OVF of the register (TCNT, or OCR)
Uint32 T0_Init_val_OVF;      //Global number of the initial value of the rest of OVFs of the register (TCNT, or OCR)
//Timer_1
Uint32 T1_OVF_No = 1;        //Global number of overflows to be used in Timer.c, & also in ISR
Uint32 T1_Init_val;          //Global number of the initial value of the first OVF of the register (TCNT, or OCR)
Uint32 T1_Init_val_OVF;      //Global number of the initial value of the rest of OVFs of the register (TCNT, or OCR)
//Timer_2
Uint32 T2_OVF_No = 1;        //Global number of overflows to be used in Timer.c, & also in ISR
Uint32 T2_Init_val;          //Global number of the initial value of the first OVF of the register (TCNT, or OCR)
Uint32 T2_Init_val_OVF;      //Global number of the initial value of the rest of OVFs of the register (TCNT, or OCR)

//ISR_T0_OVF_array
Inv_Stack T0_stack;
extern int T0_guard;
extern int T0_pause;
extern int T0_clock_starter;

//ISR_T1_OVF_varaibles
int T1_array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Stack T1_stack;
//T1_stack.arr[0] = T1_count_day_1
//T1_stack.arr[1] = T1_count_day_0
//T1_stack.arr[2] = T1_count_mon_1
//T1_stack.arr[3] = T1_count_mon_0
//T1_stack.arr[4] = T1_count_year_1
//T1_stack.arr[5] = T1_count_year_0

//T1_stack.arr[6] = T1_count_h_1
//T1_stack.arr[7] = T1_count_h_0
//T1_stack.arr[8] = T1_count_min_1
//T1_stack.arr[9] = T1_count_min_0
//T1_stack.arr[10] = T1_count_sec_1
//T1_stack.arr[11] = T1_count_sec_0

//ISR_T2_OVF_varaibles
int T2_count_sec_0 = 0; //counter to count
int T2_count_sec_1 = 0; //counter to count
int T2_count_min_0 = 0; //counter to count
int T2_count_min_1 = 0; //counter to count
int T2_count_h0 = 0; //counter to count
int T2_count_h1 = 0; //counter to count

/*Implementation of Inv_stack functions*/
void Inv_Stack_INIT(Inv_Stack *p)
{
	p->top = 6;
}
void Inv_Stack_PUSH(Inv_Stack *p, int data)
{
	int i;
	if(p->top > 0)
	{
        for(i = 0; i < 5; i++)
        p->arr[i] = p->arr[i+1];		
		p->top--;
		p->arr[5] = data;
	}
}
void Inv_Stack_Remove(Inv_Stack *p)
{
	int i;

	if(p->top < 6)
	{
        for(i = 5; i > 0; i--)
        p->arr[i] = p->arr[i-1];		
		p->arr[p->top] = 0;
		p->top++;
	}
}
/*Implementation of Stack functions*/
void Stack_INIT(Stack *p)
{
	p->top = -1;
}
void Stack_PUSH(Stack *p, int data)
{
	if(p->top < 11)
	{
		p->top++;
		p->arr[p->top] = data;
	}
}
void Stack_Remove(Stack *p)
{
	if(p->top > -1)
	{
		p->arr[p->top] = 0;
		p->top--;
	}
}

///////////////****************************Timer0 functions****************************///////////////

void TIMER0_INIT(void)
{
	/*Global Interrupt*/
	SREG = GLOBAL_INT << 7;	
	
	/*Peripheral Interrupt*/
	#if TIMER0_MODE == NORMAL_MODE
	TIMSK = TIMER0_OVF_INT | (TIMSK & 0xd4);
	#elif TIMER0_MODE == PWM_MODE
	
	#elif TIMER0_MODE == CTC_MODE
	TIMSK = (TIMER0_OCR_INT << 1) | (TIMSK & 0xd4);
	#elif TIMER0_MODE == FAST_PWM_MODE

#endif
	
}
void TIMER0_Start(void)
{
	TCCR0 = TIMER0_CLOCK;
}
void TIMER0_Stop(void)
{
	TCCR0 = T0_NO_CLOCK;
}
void TIMER0_SetDelay(Uint32 delay)
{
	Uint8 Tick_time, check = 1;
	Uint32 i; 
	Uint32 Tick_num;
	Uint8 OVF_buf; //variable to store the possible number of overflows
	Tick_time = 1024 / 16; //tick_time in micro seconds 
	Tick_num = (delay * 1000) / Tick_time; //total number of ticks needed to generate our time
	
	//Normal mode 
	#if TIMER0_MODE == NORMAL_MODE
	//case of tick_num is less than 256 (16.4 ms)
	if (Tick_num <= 256)
	{
		T0_Init_val = 256 - Tick_num; 
		TCNT0 = T0_Init_val;
	}
	//case of tick_num is bigger than 256 (16.4 ms)
	else
	{
		for (i = 130; i <= 256; i++) //check if the number of overflows is integer
		{
			OVF_buf = Tick_num / i; //buffer to store the number of OVF at every register size
			if (Tick_num == (OVF_buf * i)) 
			{
				T0_OVF_No = Tick_num / i;
				T0_Init_val = 256 - i; //initial value at the first OVF
				T0_Init_val_OVF = 256 - i; //initialize value at the rest of OVF
				TCNT0 = T0_Init_val; //initializing the TCNT0 with Init_val
				check = 0; //variable to use in checking of number of OVF being integer or decimal
			}
		}
		//
		if (check) //check if the number of OVF is decimal
		{
			T0_OVF_No += Tick_num / 256;
			T0_Init_val = 256 - (Tick_num % 256);
			T0_Init_val_OVF = 0;
			TCNT0 = T0_Init_val; //initializing the TCNT0	
		}
	}
	//CTC mode
	#elif TIMER0_MODE == CTC_MODE
	//case of tick_num is less than 256
	if (Tick_num <= 256)
	{
		T0_Init_val = Tick_num - 1;
		OCR0 = T0_Init_val;
	}
	//case of tick_num is bigger than 256
	else
	{
		for (i = 130; i <= 256; i++) //check if the number of overflows is integer
		{
			OVF_buf = Tick_num / i; //buffer o store the number of OVF at every register size
			if (Tick_num == (OVF_buf * i))
			{
				T0_OVF_No = Tick_num / i;
				T0_Init_val = i - 1;
				T0_Init_val_OVF = i - 1;
				OCR0 = T0_Init_val; //initializing the OCR0 with Init_val
				check = 0;
			}
		}
		if (check) //check if the number of OVF is decimal
		{
			T0_OVF_No += Tick_num / 256;
			T0_Init_val = (Tick_num % 256) - 1;
			T0_Init_val_OVF = 256 - 1;
			OCR0 = T0_Init_val;
		}
	}
#endif

}
ISR(TIMER0_OVF_vect)
{
	static int count_0 = 0; //counter to count the number of overflows
	count_0++;
	if (T0_OVF_No == 1)
	{
		if (count_0 == T0_OVF_No)
		{
			//write your code here
		
			count_0 = 0;
			TCNT0 = T0_Init_val;
		}
	}
	else
	{
		if (count_0 == 1)
		{
			TCNT0 = T0_Init_val_OVF;
		}
		else if (count_0 == T0_OVF_No)
		{
			//write your code here
			T0_stack.arr[5]--;
			
			if(T0_stack.arr[5] < 0)
			{
				if ((T0_stack.arr[0] > 0) || (T0_stack.arr[1] > 0) || (T0_stack.arr[2] > 0) || (T0_stack.arr[3] > 0) || (T0_stack.arr[4] > 0))
				{
					T0_stack.arr[5] = 9;
					T0_stack.arr[4]--;
				}
				else
				{
					T0_stack.arr[5] = 0;
					T0_stack.top = 6;
					T0_guard = 0;
					T0_pause = 0;
					T0_clock_starter = 0;
					TIMER0_Stop();
				}

				if(T0_stack.arr[4] < 0)
				{
					if ((T0_stack.arr[0] > 0) || (T0_stack.arr[1] > 0) || (T0_stack.arr[2] > 0) || (T0_stack.arr[3] > 0))
					{
						T0_stack.arr[4] = 5;
						T0_stack.arr[3]--;
					}
					else
					{
						T0_stack.arr[4] = 0;
					}

					if(T0_stack.arr[3] < 0)
					{
						if ((T0_stack.arr[0] > 0) || (T0_stack.arr[1] > 0) || (T0_stack.arr[2] > 0))
						{
							T0_stack.arr[3] = 9;
							T0_stack.arr[2]--;
						}
						else
						{
							T0_stack.arr[3] = 0;
						}

						if(T0_stack.arr[2] < 0)
						{
							if ((T0_stack.arr[0] > 0) || (T0_stack.arr[1] > 0))
							{
								T0_stack.arr[2] = 5;
								T0_stack.arr[1]--;
							}
							else
							{
								T0_stack.arr[2] = 0;
							}

							if((T0_stack.arr[1] < 0))
							{
								if (T0_stack.arr[0] > 0)
								{
									T0_stack.arr[1] = 9;
									T0_stack.arr[0]--;
									if (T0_stack.arr[0] < 0)
									{
										T0_stack.arr[0] = 0;
									}
								}
								else
								{
									T0_stack.arr[1] = 0;
								}
							}
						}
					}
				}
			}
			count_0 = 0;	
			TCNT0 = T0_Init_val;
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	static int count_0 = 0; //counter to count the number of overflows
	static int count_1 = 0; //counter to count
	count_0++;
	if (T0_OVF_No == 1)
	{
		if (count_0 == T0_OVF_No)
		{
			//write your code here
			count_1++;
			/*if (count_1 % 2 == 0)
			{
				(*ptr0)();
			}
			if (count_1 % 3 == 0)
			{
				(*ptr1)();
			}
			if (count_1 % 4 == 0)
			{
				(*ptr2)();
			}*/
			count_0 = 0;
			OCR0 = T0_Init_val;
		}
	}
	else
	{
		if (count_0 == 1)
		{
			OCR0 = T0_Init_val_OVF;
		}
		else if (count_0 == T0_OVF_No)
		{
			//write your code here
			count_1++;
		/*	if (count_1 % 2 == 0)
			{
				(*ptr0)();
			}
			if (count_1 % 3 == 0)
			{
				(*ptr1)();
			}
			if (count_1 % 4 == 0)
			{
				(*ptr2)();
			}*/
			count_0 = 0;
			OCR0 = T0_Init_val;
		}
	}	
}


///////////////****************************Timer1 functions****************************///////////////

void TIMER1_INIT(void)
{
	/*Global Interrupt*/
	SREG = GLOBAL_INT << 7;	
	
	/*Peripheral Interrupt*/
	#if TIMER1_MODE == NORMAL_MODE
	TIMSK = (TIMER1_OVF_INT << 2) | (TIMSK & 0xc3);
	#elif TIMER1_MODE == PWM_MODE
	
	#elif TIMER1_MODE == CTC_MODE
	TIMSK = (TIMER1_OCR_INT << 4) | (TIMSK & 0xc3);
	#elif TIMER1_MODE == FAST_PWM_MODE

#endif

	
}
void TIMER1_Start(void)
{
	TCCR1B = TIMER1_CLOCK;
}
void TIMER1_Stop(void)
{
	TCCR1B = T1_NO_CLOCK;
}
void TIMER1_SetDelay(Uint32 delay)
{
	Uint8 Tick_time, check = 1;
	Uint32 i; 
	Uint32 Tick_num;
	Uint8 OVF_buf; //variable to store the possible number of overflows
	Tick_time = 1024 / 16; //tick_time in micro seconds 
	Tick_num = (delay * 1000) / Tick_time; //total number of ticks needed to generate our time
	
	//Normal mode 
	#if TIMER1_MODE == NORMAL_MODE
	//case of tick_num is less than 65535 (4194.24 ms)
	if (Tick_num <= 65536 )
	{
		T1_Init_val = 65535 - Tick_num; 
		TCNT1 = T1_Init_val;
	}
	//case of tick_num is bigger than 65535 (4194.24 ms)
	else
	{
		for (i = 32000; i <= 65536; i++) //check if the number of overflows is integer
		{
			OVF_buf = Tick_num / i; //buffer to store the number of OVF at every register size
			if (Tick_num == (OVF_buf * i)) 
			{
				T1_OVF_No = Tick_num / i;
				T1_Init_val = 65536 - i; //initial value at the first OVF
				T1_Init_val_OVF = 65536 - i; //initialize value at the rest of OVF
				TCNT1 = T1_Init_val; //initializing the TCNT0 with Init_val
				check = 0; //variable to use in checking of number of OVF being integer or decimal
			}
		}
		//
		if (check) //check if the number of OVF is decimal
		{
			T1_OVF_No += Tick_num / 65536;
			T1_Init_val = 65536 - (Tick_num % 65536);
			T1_Init_val_OVF = 0;
			TCNT1 = T1_Init_val; //initializing the TCNT0	
		}
	}
	//CTC mode
	#elif TIMER1_MODE == CTC_MODE
	//case of tick_num is less than 256
	if (Tick_num <= 65536)
	{
		T1_Init_val = Tick_num - 1;
		OCR1A = T1_Init_val;
	}
	//case of tick_num is bigger than 256
	else
	{
		for (i = 32000; i <= 65536; i++) //check if the number of overflows is integer
		{
			OVF_buf = Tick_num / i; //buffer o store the number of OVF at every register size
			if (Tick_num == (OVF_buf * i))
			{
				T1_OVF_No = Tick_num / i;
				T1_Init_val = i - 1;
				T1_Init_val_OVF = i - 1;
				OCR1A = T1_Init_val; //initializing the OCR0 with Init_val
				check = 0;
			}
		}
		if (check) //check if the number of OVF is decimal
		{
			T1_OVF_No += Tick_num / 65536;
			T1_Init_val = (Tick_num % 65536) - 1;
			T1_Init_val_OVF = 65536 - 1;
			OCR1A = T1_Init_val;
		}
	}
#endif

}
ISR(TIMER1_OVF_vect)
{
	static int count_0 = 0; //counter to count the number of overflows
	int h_max = T1_stack.arr[6] == 2?3:9; //counter to count 
	int day_max = T1_stack.arr[0] == (T1_array[(T1_stack.arr[2]*10)+ T1_stack.arr[3] - 1] / 10)?(T1_array[(T1_stack.arr[2]*10)+ T1_stack.arr[3] - 1] % 10):9; //counter to count   
	int day_init = T1_stack.arr[0] == (T1_array[(T1_stack.arr[2]*10)+ T1_stack.arr[3] - 1] / 10)?1:0; //counter to count  
	int mon_max = T1_stack.arr[2] == 1?2:9; //counter to count 
	int mon_init = T1_stack.arr[2] == 1?1:0; //counter to count  
	

	count_0++;
	if (T1_OVF_No == 1)
	{
		if (count_0 == T1_OVF_No)
		{
			//write your code here
			T1_stack.arr[11]++;
					
			if(T1_stack.arr[11] > 9)
			{
				T1_stack.arr[11] = 0;
				T1_stack.arr[10]++;

				if(T1_stack.arr[10] > 5)
				{
					T1_stack.arr[10] = 0;
					T1_stack.arr[9]++;

					if(T1_stack.arr[9] > 9)
					{
						T1_stack.arr[9] = 0;
						T1_stack.arr[8]++;

						if(T1_stack.arr[8] > 5)
						{
							T1_stack.arr[8] = 0;
							T1_stack.arr[7]++;

							if(T1_stack.arr[7] > h_max)
							{
								T1_stack.arr[7] = 0;
								T1_stack.arr[6]++;

								if(T1_stack.arr[6] > 2)
								{
									T1_stack.arr[6] = 0;
									T1_stack.arr[1]++;
									
									if (T1_stack.arr[1] > day_max)
									{
										T1_stack.arr[1] = day_init;
										T1_stack.arr[0]++;
										
										if (T1_stack.arr[0] > (T1_array[(T1_stack.arr[2]*10)+ T1_stack.arr[3] - 1] / 10))
										{
											T1_stack.arr[0] = 0;
											T1_stack.arr[3]++;
											
											if (T1_stack.arr[3] > mon_max)
											{
												T1_stack.arr[3] = mon_init;
												T1_stack.arr[2]++;

												if (T1_stack.arr[2] > 1)
												{
													T1_stack.arr[2] = 0;
													T1_stack.arr[5]++;
													
													if (T1_stack.arr[5] > 9)
													{
														T1_stack.arr[5] = 0;
														T1_stack.arr[4]++;
														
														if (T1_stack.arr[4] > 9)
														{
															T1_stack.arr[4] = 0;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}		
			count_0 = 0;
			TCNT1 = T1_Init_val;
		}
	}
	else
	{
		if (count_0 == 1)
		{
			TCNT1 = T1_Init_val_OVF;
		}
		else if (count_0 == T1_OVF_No)
		{
			//write your code here

			count_0 = 0;	
			TCNT1 = T1_Init_val;
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	static int count_0 = 0; //counter to count the number of overflows
	static int count_1 = 0; //counter to count
	count_0++;
	if (T1_OVF_No == 1)
	{
		if (count_0 == T1_OVF_No)
		{
			//write your code here
			count_1++;

			count_0 = 0;
			OCR1A = T1_Init_val;
		}
	}
	else
	{
		if (count_0 == 1)
		{
			OCR1A = T1_Init_val_OVF;
		}
		else if (count_0 == T1_OVF_No)
		{
			//write your code here
			count_1++;
		/*	if (count_1 % 2 == 0)
			{
				(*ptr0)();
			}
			if (count_1 % 3 == 0)
			{
				(*ptr1)();
			}
			if (count_1 % 4 == 0)
			{
				(*ptr2)();
			}*/
			count_0 = 0;
			OCR1A = T1_Init_val;
		}
	}	
}

///////////////****************************Timer2 functions****************************///////////////

void TIMER2_INIT(void)
{
	/*Global Interrupt*/
	SREG = GLOBAL_INT << 7;
	
	/*Peripheral Interrupt*/
	#if TIMER2_MODE == NORMAL_MODE
	TIMSK = (TIMER2_OVF_INT << 6) | (TIMSK & 0x17);
	#elif TIMER2_MODE == PWM_MODE
	
	#elif TIMER2_MODE == CTC_MODE
	TIMSK = (TIMER2_OCR_INT << 7) | (TIMSK & 0x17);
	#elif TIMER2_MODE == FAST_PWM_MODE

	#endif

	
}
void TIMER2_Start(void)
{
	TCCR2 = TIMER2_CLOCK;
}
void TIMER2_Stop(void)
{
	TCCR2 = T2_NO_CLOCK;
}
void TIMER2_SetDelay(Uint32 delay)
{
	Uint8 Tick_time, check = 1;
	Uint32 i;
	Uint32 Tick_num;
	Uint8 OVF_buf; //variable to store the possible number of overflows
	Tick_time = 1024 / 16; //tick_time in micro seconds
	Tick_num = (delay * 1000) / Tick_time; //total number of ticks needed to generate our time
	
	//Normal mode
	#if TIMER2_MODE == NORMAL_MODE
	//case of tick_num is less than 256 (16.4 ms)
	if (Tick_num <= 256)
	{
		T2_Init_val = 256 - Tick_num;
		TCNT2 = T2_Init_val;
	}
	//case of tick_num is bigger than 256 (16.4 ms)
	else
	{
		for (i = 130; i <= 256; i++) //check if the number of overflows is integer
		{
			OVF_buf = Tick_num / i; //buffer to store the number of OVF at every register size
			if (Tick_num == (OVF_buf * i))
			{
				T2_OVF_No = Tick_num / i;
				T2_Init_val = 256 - i; //initial value at the first OVF
				T2_Init_val_OVF = 256 - i; //initialize value at the rest of OVF
				TCNT2 = T2_Init_val; //initializing the TCNT0 with Init_val
				check = 0; //variable to use in checking of number of OVF being integer or decimal
			}
		}
		//
		if (check) //check if the number of OVF is decimal
		{
			T2_OVF_No += Tick_num / 256;
			T2_Init_val = 256 - (Tick_num % 256);
			T2_Init_val_OVF = 0;
			TCNT2 = T2_Init_val; //initializing the TCNT0
		}
	}
	//CTC mode
	#elif TIMER2_MODE == CTC_MODE
	//case of tick_num is less than 256
	if (Tick_num <= 256)
	{
		T2_Init_val = Tick_num - 1;
		OCR2 = T2_Init_val;
	}
	//case of tick_num is bigger than 256
	else
	{
		for (i = 130; i <= 256; i++) //check if the number of overflows is integer
		{
			OVF_buf = Tick_num / i; //buffer o store the number of OVF at every register size
			if (Tick_num == (OVF_buf * i))
			{
				T2_OVF_No = Tick_num / i;
				T2_Init_val = i - 1;
				T2_Init_val_OVF = i - 1;
				OCR2 = T2_Init_val; //initializing the OCR0 with Init_val
				check = 0;
			}
		}
		if (check) //check if the number of OVF is decimal
		{
			T2_OVF_No += Tick_num / 256;
			T2_Init_val = (Tick_num % 256) - 1;
			T2_Init_val_OVF = 256 - 1;
			OCR2 = T2_Init_val;
		}
	}
	#endif

}
ISR(TIMER2_OVF_vect)
{
	static int count_0 = 0; //counter to count the number of overflows
	static int h_max = 10; //counter to count  
	count_0++;
	if (T2_OVF_No == 1)
	{
		if (count_0 == T2_OVF_No)
		{
			//write your code here

			count_0 = 0;
			TCNT2 = T2_Init_val;
		}
	}
	else
	{
		if (count_0 == 1)
		{
			TCNT2 = T2_Init_val_OVF;
		}
		else if (count_0 == T2_OVF_No)
		{
			//write your code here
			T2_count_sec_0++;
			
			if(T2_count_sec_0 > 9)
			{
				T2_count_sec_0 = 0;
				T2_count_sec_1++;

				if(T2_count_sec_1 > 5)
				{
					T2_count_sec_1 = 0;
					T2_count_min_0++;

					if(T2_count_min_0 > 9)
					{
						T2_count_min_0 = 0;
						T2_count_min_1++;

						if(T2_count_min_1 > 5)
						{
							T2_count_min_1 = 0;
							T2_count_h0++;

							if(T2_count_h0 > h_max - 1)
							{
								T2_count_h0 = 0;
								T2_count_h1++;

								if (T2_count_h1 == 2)
								{
									h_max = 4;
								}

								if(T2_count_h1 > 2)
								{
									T2_count_h1 = 0;
								}
							}
						}
					}
				}
			}
			count_0 = 0;
			TCNT2 = T2_Init_val;
		}
	}
}

ISR(TIMER2_COMP_vect)
{
	static int count_0 = 0; //counter to count the number of overflows
	static int count_1 = 0; //counter to count
	count_0++;
	if (T2_OVF_No == 1)
	{
		if (count_0 == T2_OVF_No)
		{
			//write your code here
			count_1++;
			/*if (count_1 % 2 == 0)
			{
				(*ptr0)();
			}
			if (count_1 % 3 == 0)
			{
				(*ptr1)();
			}
			if (count_1 % 4 == 0)
			{
				(*ptr2)();
			}*/
			count_0 = 0;
			OCR2 = T2_Init_val;
		}
	}
	else
	{
		if (count_0 == 1)
		{
			OCR2 = T2_Init_val_OVF;
		}
		else if (count_0 == T2_OVF_No)
		{
			//write your code here
			count_1++;
		/*	if (count_1 % 2 == 0)
			{
				(*ptr0)();
			}
			if (count_1 % 3 == 0)
			{
				(*ptr1)();
			}
			if (count_1 % 4 == 0)
			{
				(*ptr2)();
			}*/
			count_0 = 0;
			OCR2 = T2_Init_val;
		}
	}
}
