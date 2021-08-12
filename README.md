# Digital-Watch
Embedded Digital watch with four modes (Alarm, Timer, Clock, Stopwatch)
# Purpose of the project
- there are four purposes of the project:
1. Display the current ( DD/MM/YYYY , hh:mm:ss ) time in Clock mode.
2. Set count down timer from any time up to  99 hours, 59 minutes, 59 seconds in Timer mode.
3. Set stopwatch to count up from 00 hours, 00 minutes, 00 seconds up to 99 hours, 59 minutes, 59 seconds in Stopwatch mode.
4. Add, modify, remove up to 20 Alarm in Alarm mode. (Under Development)


# Components of the project
− The project consists of:
1. 1 X Controller (ATMEGA32)
2. 1 X EEPORM (AT24C16)
3. 1 X Keypad (4 X 4)
4. 1 X LCD 16 X 2
5. 1 X Buzzer

# Implementation of the project
- This digital watch has four modes, Alarm, Timer, Clock, & Stopwatch. for each one of these modes (Timer, Clock, Stopwatch), i used a dedicated timer (OVF) to control it.
- the project consists of the MC ATMEGA32, LCD, Keypad (4X4),  couple of push buttons, & Buzzer.
- in this project i used Modular programming, with drivers for MCAL peripherals like Timer, DIO, and drivers for HAL devices like LCD, Keypad, Buzzer, Push buttons, all that with Interrupts, & callback functions.
