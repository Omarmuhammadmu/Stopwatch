/****************************************************************
  Project name: Mini-project 2 (Interfacing 1)
  Author: Omar Muhammad
  Description: Stop watch project
  Created on: Sep 12, 2022
 *****************************************************************/


#include<avr/io.h>
#include<avr/interrupt.h>
#include"MCAL/timer.h"
#include"MCAL/std_types.h"
#include "HAL/seven_segment.h"


uint8 seconds = 0;
uint8 minutes = 0;
uint8 hours = 0;


/* Interrupt Service Routine for INT0 to reset stop watch*/
ISR (INT0_vect)
{
	seconds = 0;
	minutes = 0;
	hours = 0;
}

/* Interrupt Service Routine for INT1 to pause counting */
ISR (INT1_vect)
{
	/* For CS12=0 CS11=0 CS10=0, No clock source (Timer/Counter stopped).*/
	TCCR1B &= ~(1<<CS10) &~(1<<CS12) &~(1<<CS11);
}

/* Interrupt Service Routine for INT2 to resume counting */
ISR (INT2_vect)
{
	/* For CS12=1 CS11=0 CS10=1, clkI/O/1024 (From prescaler) and the counter resumes*/
	TCCR1B |= (1<<CS10) | (1<<CS12);
}

void counter (void)
{
	seconds++;
	if(seconds == 60)
	{
		seconds = 0;
		minutes++;
	}
	if(minutes == 60)
	{
		minutes = 0;
		hours++;
	}
	if(hours == 24)
	{
		hours = 0;
	}
}

//Initializing interrupt 1
void INT0_Init(void)
{
	DDRD &= ~(1<<PD2);    // Configure  pin PD2 in PORTD as input pin
	PORTD |= (1<<PD2);    // Activate the internal pull up resistor

	MCUCR |= (1<<ISC01);  // Falling edge generates interrupt request
	GICR |= (1<<INT0);    // Enable the Interrupt 0
}

//Initializing interrupt 2
void INT1_Init(void)
{
	DDRD &= ~(1<<PD3);                // Configure  pin PD3 in PORTD as input pin
	PORTD &=~(1<<PD3);                // Disable internal pull up

	MCUCR |= (1<<ISC11) | (1<<ISC10); // Raising edge generates interrupt request
	GICR |= (1<<INT1);                // Enable the Interrupt 1
}

//Initializing interrupt 3
void INT2_Init(void)
{
	DDRB &= ~(1<<PB2);    // Configure  pin PB2 in PORTB as input pin
	PORTB |= (1<<PB2);    // Activate the internal pull up resistor

	MCUCSR &= ~(1<<ISC2);  // Falling edge generates interrupt request
	GICR |= (1<<INT2);    // Enable the Interrupt 2
}

int main(void)
{
	/* setting the callBack function to count seconds */
	Timer1_setCallBack(counter);

	/*
	 * For System clock = 1Mhz and prescale F_CPU/1024.
	 * Timer frequency will be around 1Mhz, Ttimer = 1ms
	 * So we just need 1000 counts to get 1s period.
	 */
	Timer1_ConfigType timer1Config = {0,1000,F_CPU_1024,CTC};

	//Initializing Seven seg
	SEVENSEGMENT_init();

	SREG |= (1<<7);  /* Enable global interrupts in MC */

	//Initializing timer1, INT0, INT1, INT2
	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_init(&timer1Config);

	while(1)
	{
		//Display on multiplexed seven segment simultaneously
		SEVENSEGMENT_display(seconds,minutes,hours);
	}
}
