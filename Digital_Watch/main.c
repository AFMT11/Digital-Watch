/*
 * Digital_Watch
 *
 * Created: 7/17/2021 8:36:11 PM
 * Author : Ahmed Atef
 
 This program has four modes:
 1- Alarm
 2- Timer
 3- Clock
 4- Stopwatch
 
 */ 
#include "Timer.h"
#include "LCD.h"
#include "Button.h"
#include "Keypad.h"
#include "Buzz.h"

#define F_CPU 16000000
#include <util/delay.h>

/*Timer0 global variables*/
extern Inv_Stack T0_stack;	//Stack that contains the array and the pointer of that array.
int T0_guard = 0;			//Variable that is used to guard the timer from writing on it while running
int T0_pause = 2;			//Variable that by modifying its value, we can set whether to flash the screen or not in Timer mode.
int T0_clock_starter = 0;	//Variable that used to decide what will happened if the user
                            //press the button '#' while there is a time remains in timer 
							//or the timer currently reaches zero

/*Timer1 global variables*/
extern Stack T1_stack;		//Stack that contains the array and the pointer of that array.
int T1_guard = 1;			//Variable that is used to guard the timer from writing on it while running

/*Timer2 global variables*/
extern int T2_count_sec_0; //counter to count
extern int T2_count_sec_1; //counter to count
extern int T2_count_min_0; //counter to count
extern int T2_count_min_1; //counter to count
extern int T2_count_h0; //counter to count
extern int T2_count_h1; //counter to count

//four variables to be used at the first of each mode to make
//A specific section of code to be executed only once even if
//the user pressed more than one time on the same button mode
int modeA = 0;
int modeB = 0;
int modeC = 0;
int modeD = 0;

//in timer mode we use three variables that are used
//to convert the entered time into appropriate time formula 
int hours;
int minutes;
int seconds;

int main(void)
{	
	/*General variables & functions*/
	int Timer_delay = 1000;	//Time in ms to be generated in all timers
	
	int Keypad_val = 0;		//Variable that receives the value of keypad
	
	int selector0 = 0;		//Variable that store the received value from keypad,
							//If the value of the pressed button between 65 & 68
							
	int selector1 = 0;		//Variable that store the received value from keypad,
							//If the value of the pressed button anything that 
							//Is not in range of 65 & 68
	
	Uint8 Background_message[] = "Digital Watch";
	
	Keypad_INIT();
	LCD_INIT();
	
	/*Alarm mode*/
	Uint8 A_str[] = "Alarm:";
	
	/*Timer mode*/
	int T0_SS_Count = 1;	//the variable that make us be able to use one button for 
	                        //two functionalities, and at one press the value of that 
							//variable will be incremented, then we check if that value 
							//is dividable on 2, if it is then do function (start the timer)
							//if not do another function (stop the timer)
	int T0_stack_Index;
	Uint8 T_str[] = "Timer:";
	TIMER0_INIT();
	TIMER0_SetDelay(Timer_delay);
	Inv_Stack_INIT(&T0_stack);
	
	/*Clock mode*/
	int Tone_counter = 1;	//In clock mode, to control if we want from the system
							//to generate a beep every 1 hour or not, we use that
							//variable so that while the clock is running and if we
							//pressed on the button '*' it will increment the value
							//of that variable and check if that value can be divided
							//on 2, so if it can then we modify the value of the variable
							//Tone_switch to 1, but if the value of Tone_counter can't
							//be divided on 2 then we modify the value of the variable
							//Tone_switch to 0, ans so forth.

	int Tone_switch = 0;	//Variable that will be checked if its value is 1 or 0,
							//so if it is 1 then it will allow that every one hour it
							//will make 2 beeps, but if it value is 0 then it will
							//mute the system from beeping and display on the screen
							//the letter 'M' for mute
	
	int Tone2_Buff = 0;		//A variable to compare the value in it with the current
							//value in specific element of the array of the stack.	
							
	int T1_SS_Count = 0;	//the variable that make us be able to use one button for
							//two functionalities, and at one press the value of that
							//variable will be incremented, then we check if that value
							//is dividable on 2, if it is then do function (start the timer)
							//if not do another function (stop the timer)
	Uint8 C_str[] = "Clock:";
	int T1_stack_Index;
	TIMER1_INIT();
	TIMER1_SetDelay(Timer_delay);
	TIMER1_Start();	
	Stack_INIT(&T1_stack);	
	
	/*Stop Watch mode*/
	int T2_SS_Count = 1;	//the variable that make us be able to use one button for
							//two functionalities, and at one press the value of that
							//variable will be incremented, then we check if that value
							//is dividable on 2, if it is then do function (start the timer)
							//if not do another function (stop the timer)
							
	int T2_pause = 2;		//Variable that by modifying its value, we can set whether to flash the screen or not in Timer mode.
	Uint8 S_str[] = "Stopwatch:";
	TIMER2_INIT();
	TIMER2_SetDelay(Timer_delay);
	
	/*Background Message*/
	LCD_GoTo(0,0);
	LCD_WriteSTRING(Background_message);
	
	
    while (1) 
    {
		Keypad_val = Keypad_GetVal();      //store the value of the pressed button
		if (Keypad_val >= 65 && Keypad_val <= 68) //check on the value of Keypad_val
		selector0 = Keypad_val;
		else
		selector1 = Keypad_val;
	
		switch(selector0)
		{
			/*Alarm mode (Based on Timer 1) (In Development)*/
			case 'A':
			
			if (modeA == 0)       //that section will be executed for only 1 time,
			{                     //even if we pressed the button 'A' more than 1 time
				Buzz_Tone1();
				modeA = 1;
				modeB = 0;
				modeC = 0;
				modeD = 0;
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteSTRING(A_str);				
			}
			break;
			
			/*Timer mode (Timer 0)*/
			case 'B':
			if (modeB == 0)		//that section will be executed for only 1 time,
			{					//even if we pressed the button 'B' more than 1 time
				Buzz_Tone1();
				modeA = 0;
				modeB = 1;
				modeC = 0;
				modeD = 0;
				LCD_Clear();
				
				LCD_GoTo(0,0);
				LCD_WriteSTRING(T_str);					
			}
			
			//If we pressed on timer mode then pause the stopwatch
			//whether it is running or not, and make the value 
			//of T2_SS_count to be 1, so that when we press on 
			//the button '#' at stopwatch mode to restart again it will increment 
			//that value to be 2 so that it can be divided 
			//on 2 which will make the condition to be true 
			T2_SS_Count = 1;
			TIMER2_Stop();
			
			//in this condition we want to write on the timer, but 
			//in order to write on the timer, there are two conditions
			//
			//1- that the value of T0_guard is 0 as the value of that 
			//variable turn to 1 when the timer is running, and it is still
			// the value of 1 even if we pause the timer, can that value 
			//can be 0 in 2 cases; the first case when we press on clear
			//timer button, the other case is when the timer count down 
			//all the way to 0, then in ISR we modify the value of it to be 0
			//
			//2- that the value of T0_pause is 2, as the value of that variable 
			//turns to 0 when we press on '#' to pause the timer, and also when
			//timer count down to 0, and the value of that variable could be 2
			//in two case; the first one when the timer count down to 0 and starts 
			//to beep, then if we press on '#' button it will disable the beep
			//and also stop the timer, and make the value of T0_pause to be 2
			//which means it will stop flashing, the second case is when we press 
			//on clear timer button, which will also stop the timer and make the value
			//of T0_pause to be 2
			//
			//then if those two conditions are true then it will go to check if 
			//the pressed button is a number or not, and if it is a number then 
			//push it in the inverted Stack
			if ((T0_guard == 0) && (T0_pause == 2))
			{
				if (selector1 >= 48 && selector1 <= 57)
				{
					Buzz_Tone1();
					Inv_Stack_PUSH(&T0_stack, selector1-48);
				}
			
			}
			if (selector1 == '#') //check if the button '#' is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				T0_SS_Count++;
				
				//for loop to check if there are any element of the 
				//elements of the array its value is > 0, and if yes 
				//modify the value of the variable T0_clock_starter to be 1
				for (T0_stack_Index = 0;T0_stack_Index < 6; T0_stack_Index++)
				{
					if (T0_stack.arr[T0_stack_Index] > 0)
					{
						T0_clock_starter = 1;
					}
				}
				
				//the value of that variable is going to be 1 if and only if any elements 
				//of the elements of the array, its value is bigger than 0, which means
				//that there is still time left to count down, and if so, there are two options
				//whether to start the timer, or to pause it, but if there is no time left 
				//then the only thing that it can do is to disable the flashing, and modify
				//the value of T0_SS_count to be 1, so that the first thing to do after reentering 
				//the time we want to count down from is to start the timer
				if (T0_clock_starter)
				{
					if (T0_SS_Count % 2 == 0) //check if the incremented value can be divided on 2 or not!
					{
						//here is the code which by it, it can convert the entered time 
						//into appropriate time formula.
						hours   = (T0_stack.arr[0]*10) + T0_stack.arr[1];
						minutes = (T0_stack.arr[2]*10) + T0_stack.arr[3];
						seconds = (T0_stack.arr[4]*10) + T0_stack.arr[5];
						
						
						minutes += (seconds / 60);
						seconds %= 60;
						hours += (minutes / 60);
						if (hours > 99)
						{
							hours = 99;
						}
						minutes %= 60;
						if (minutes > 99)
						{
							minutes = 99;
						}
						//the following lines are to modify the value of the elements
						//of the array of the Stack with the correct values
						T0_stack.arr[0] = hours / 10;
						T0_stack.arr[1] = hours % 10;
						
						T0_stack.arr[2] = minutes / 10;
						T0_stack.arr[3] = minutes % 10;
						
						T0_stack.arr[4] = seconds / 10;
						T0_stack.arr[5] = seconds % 10;
						
						TIMER0_Start();
						T0_guard = 1; //the guard is 1 so that we can't write into the timer.
						T0_pause = 2; //the pause is 2 which means that there is no flashing.
					}
					else
					{
						TIMER0_Stop();
						T0_pause = 0;
					}				
				}
				else //if the timer count down to zeros
				{
					T0_SS_Count = 1;
					T0_pause = 2;
				}
			}
			else if (selector1 == '*') //check if the button '*' is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				if (T0_guard == 0) // if the guard is 0 then we can modify the elements of the array
				{
					Inv_Stack_Remove(&T0_stack);
				}
			}	
			else if(BUTTON0_GetPinVal()) //check if the button 0 is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				T0_SS_Count = 1;		//the value of T0_SS_count to be 1, so that the first thing to do after reentering
										//the time we want to count down from is to start the timer
				
				T0_stack.top = 6;
				T0_clock_starter = 0;	
				T0_guard = 0;
				T0_pause = 2;
				T0_stack.arr[0] = 0;
				T0_stack.arr[1] = 0;
				T0_stack.arr[2] = 0;
				T0_stack.arr[3] = 0;
				T0_stack.arr[4] = 0;
				T0_stack.arr[5] = 0;
				TIMER0_Stop();
			}	
			
			//the value of T0_pause can be 0 in two cases;
			//1- when we press on '#' button while there is time
			//remains in the timer
			//2- in ISR function after the timer count down to zeros 
			//and starts to beep, it modify the value of T0_pause to be 0
			//so that it can start flashing.
			//
			//
			//we want to make the screen to flash in two cases;
			//1- the first case when we press on the button '#' after 
			//starting the timer
			//2- the second case when the timer count down to zeros
			//but with generating 4 beeps continuously
			if (T0_pause == 0)
			{
				LCD_Clear();
				if (T0_clock_starter == 0) 
				{
					BUZZ_OFF();
				}
				_delay_ms(100);
				T0_pause = 1;
			}
			else if (T0_pause == 1)
			{
				LCD_GoTo(0,0);
				LCD_WriteSTRING(T_str);				
				LCD_GoTo(1,9);
				LCD_WriteCHAR('h');
				LCD_GoTo(1,12);
				LCD_WriteCHAR('m');
				LCD_GoTo(1,15);
				LCD_WriteCHAR('s');				
				
				LCD_GoTo(1,7);
				LCD_WriteINTEGER(T0_stack.arr[0]);
				LCD_GoTo(1,8);
				LCD_WriteINTEGER(T0_stack.arr[1]);
				LCD_GoTo(1,10);
				LCD_WriteINTEGER(T0_stack.arr[2]);
				LCD_GoTo(1,11);
				LCD_WriteINTEGER(T0_stack.arr[3]);
				LCD_GoTo(1,13);
				LCD_WriteINTEGER(T0_stack.arr[4]);
				LCD_GoTo(1,14);
				LCD_WriteINTEGER(T0_stack.arr[5]);
				
				if (T0_clock_starter == 0)
				{
					Buzz_Tone0();
				}				
				_delay_ms(100);
				T0_pause = 0;
			}
			//display the data on the screen
		    LCD_GoTo(0,0);
		    LCD_WriteSTRING(T_str);				
			LCD_GoTo(1,9);
			LCD_WriteCHAR('h');
			LCD_GoTo(1,12);
			LCD_WriteCHAR('m');
			LCD_GoTo(1,15);
			LCD_WriteCHAR('s');
			
			LCD_GoTo(1,7);
			LCD_WriteINTEGER(T0_stack.arr[0]);
			LCD_GoTo(1,8);
			LCD_WriteINTEGER(T0_stack.arr[1]);
			LCD_GoTo(1,10);
			LCD_WriteINTEGER(T0_stack.arr[2]);
			LCD_GoTo(1,11);
			LCD_WriteINTEGER(T0_stack.arr[3]);
			LCD_GoTo(1,13);
			LCD_WriteINTEGER(T0_stack.arr[4]);
			LCD_GoTo(1,14);
			LCD_WriteINTEGER(T0_stack.arr[5]);
					
			break;
			
			/*Clock mode (Timer 1)*/
			case 'C':
			if (modeC == 0)		//that section will be executed for only 1 time,
			{					//even if we pressed the button 'C' more than 1 time
				Buzz_Tone1();
				modeA = 0;
				modeB = 0;
				modeC = 1;
				modeD = 0;
				LCD_Clear();
				
				LCD_GoTo(0,0);
				LCD_WriteSTRING(C_str);
				/*clock separators*/
				LCD_GoTo(1,10);
				LCD_WriteCHAR(':');
				LCD_GoTo(1,13);
				LCD_WriteCHAR(':');
				/*date separators*/
				LCD_GoTo(0,10);
				LCD_WriteCHAR('/');
				LCD_GoTo(0,13);
				LCD_WriteCHAR('/');
			}
			
			T0_SS_Count = 1;
			TIMER0_Stop();
			T2_SS_Count = 1;
			TIMER2_Stop();
			
			if (T1_guard == 0)
			{
				if (selector1 >= 48 && selector1 <= 57)
				{
					Buzz_Tone1();
					Stack_PUSH(&T1_stack, selector1-48);
				}
			}
						
			if (selector1 == '#') //check if the button '#' is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				T1_SS_Count++;
				if (T1_SS_Count % 2 == 0)
				{
					T1_guard = 1;
					T1_stack.top = 11;
					TIMER1_Start();
				}
				else
				{
					T1_guard = 0;
					TIMER1_Stop();
				}
				
			}
			else if (selector1 == '*') //check if the button '*' is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				if (T1_guard == 0)
				{
					Stack_Remove(&T1_stack);
				}
				else
				{
					Tone_counter++;
					if (Tone_counter % 2 == 0)
					{
						Tone_switch = 1;	
					}
					else
					{
						Tone_switch = 0;
					}
				}
			}
			else if(BUTTON0_GetPinVal()) //check if the button 0 is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				T1_SS_Count = 1;
				T1_stack.top = -1;
				T1_guard = 0;
				
				for(T1_stack_Index = 0; T1_stack_Index < 12; T1_stack_Index++)
				{
					T1_stack.arr[T1_stack_Index] = 0;
				}				
				TIMER1_Stop();
			}	
			//check if the Tone switch is 1 or 0
			if (Tone_switch)
			{	
				LCD_GoTo(1,0);
				LCD_WriteCHAR(32);				
				if (Tone2_Buff != T1_stack.arr[7])
				{
					Buzz_Tone2();
					Tone2_Buff = T1_stack.arr[7];
				}						
			}
			else
			{
				LCD_GoTo(1,0);
				LCD_WriteCHAR('M');				
			}
			
			//display the data on the screen
			LCD_GoTo(0,8);
			LCD_WriteINTEGER(T1_stack.arr[0]);
			LCD_GoTo(0,9);
			LCD_WriteINTEGER(T1_stack.arr[1]);
			LCD_GoTo(0,11);
			LCD_WriteINTEGER(T1_stack.arr[2]);
			LCD_GoTo(0,12);
			LCD_WriteINTEGER(T1_stack.arr[3]);
			LCD_GoTo(0,14);
			LCD_WriteINTEGER(T1_stack.arr[4]);
			LCD_GoTo(0,15);
			LCD_WriteINTEGER(T1_stack.arr[5]);															
			
			LCD_GoTo(1,8);
			LCD_WriteINTEGER(T1_stack.arr[6]);
			LCD_GoTo(1,9);
			LCD_WriteINTEGER(T1_stack.arr[7]);
			LCD_GoTo(1,11);
			LCD_WriteINTEGER(T1_stack.arr[8]);
			LCD_GoTo(1,12);
			LCD_WriteINTEGER(T1_stack.arr[9]);
			LCD_GoTo(1,14);
			LCD_WriteINTEGER(T1_stack.arr[10]);
			LCD_GoTo(1,15);
			LCD_WriteINTEGER(T1_stack.arr[11]);
			break;			
			
			/*Stopwatch mode (Timer 2)*/
			case 'D':
			if (modeD == 0)		//that section will be executed for only 1 time,
			{					//even if we pressed the button 'D' more than 1 time
				Buzz_Tone1();
				modeA = 0;
				modeB = 0;
				modeC = 0;
				modeD = 1;
				LCD_Clear();
				
				LCD_GoTo(0,0);
				LCD_WriteSTRING(S_str);				
			}
			
			T0_SS_Count = 1;
			TIMER0_Stop();
			
			if (selector1 == '#') //check if the button '#' is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				T2_SS_Count++;
				if (T2_SS_Count % 2 == 0)
				{				
					TIMER2_Start();
					T2_pause = 2;
				}
				else
				{
					TIMER2_Stop();
					T2_pause = 0;
				}
			}
			else if(BUTTON0_GetPinVal()) //check if the button 0 is pressed, and if yes do the following:
			{
				Buzz_Tone1();
				T2_SS_Count = 1;
				T2_pause = 2;
				T2_count_sec_0 = 0;
				T2_count_sec_1 = 0;
				T2_count_min_0 = 0;
				T2_count_min_1 = 0;
				T2_count_h0 = 0;
				T2_count_h1 = 0;
				TIMER2_Stop();
			}
			if (T2_pause == 0)
			{
				LCD_Clear();
				_delay_ms(400);
				T2_pause = 1;
			}
			else if (T2_pause == 1)
			{
				LCD_GoTo(0,0);
				LCD_WriteSTRING(S_str);				
				LCD_GoTo(1,10);
				LCD_WriteCHAR(':');
				LCD_GoTo(1,13);
				LCD_WriteCHAR(':');
				
				LCD_GoTo(1,8);
				LCD_WriteINTEGER(T2_count_h1);
				LCD_GoTo(1,9);
				LCD_WriteINTEGER(T2_count_h0);
				LCD_GoTo(1,11);
				LCD_WriteINTEGER(T2_count_min_1);
				LCD_GoTo(1,12);
				LCD_WriteINTEGER(T2_count_min_0);
				LCD_GoTo(1,14);
				LCD_WriteINTEGER(T2_count_sec_1);
				LCD_GoTo(1,15);
				LCD_WriteINTEGER(T2_count_sec_0);
				
				_delay_ms(400);
				T2_pause = 0;
			}
			LCD_GoTo(0,0);
			LCD_WriteSTRING(S_str);												
			LCD_GoTo(1,10);
			LCD_WriteCHAR(':');
			LCD_GoTo(1,13);
			LCD_WriteCHAR(':');
							
			LCD_GoTo(1,8);
			LCD_WriteINTEGER(T2_count_h1);
			LCD_GoTo(1,9);
			LCD_WriteINTEGER(T2_count_h0);
			LCD_GoTo(1,11);
			LCD_WriteINTEGER(T2_count_min_1);
			LCD_GoTo(1,12);
			LCD_WriteINTEGER(T2_count_min_0);
			LCD_GoTo(1,14);
			LCD_WriteINTEGER(T2_count_sec_1);
			LCD_GoTo(1,15);
			LCD_WriteINTEGER(T2_count_sec_0);			
			break;
			
			default:
			break;						
		}
	}
}

