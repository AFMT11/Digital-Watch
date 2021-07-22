/*
 * Interrupts_CFG.h
 *
 * Created: 7/10/2021 11:41:12 PM
 *  Author: ahmed
 */ 


#ifndef INTERRUPTS_CFG_H_
#define INTERRUPTS_CFG_H_

#include "Bit_Math.h"
#include "std.h"
#include "MC_Selector.h"
/*Global Interrupt Selection*/
#define GLOBAL_INT                Global_Interupt_Enable

/*Timer0 Interrupt Selection*/
#define TIMER0_OVF_INT            Peripheral_Interupt_Enable
#define TIMER0_OCR_INT            Peripheral_Interupt_Disable

/*Timer1 Interrupt Selection*/
#define TIMER1_OVF_INT            Peripheral_Interupt_Enable
#define TIMER1_OCR_INT            Peripheral_Interupt_Disable

/*Timer2 Interrupt Selection*/
#define TIMER2_OVF_INT            Peripheral_Interupt_Enable
#define TIMER2_OCR_INT            Peripheral_Interupt_Disable

#endif /* INTERRUPTS_CFG_H_ */