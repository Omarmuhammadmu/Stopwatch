/******************************************************************************
 *
 * Module: 7_segment
 *
 * File Name: seven_segment.c
 *
 * Description: Source file for the Multiplexed seven segment
 *
 * Author: Omar Muhammad
 *
 ******************************************************************************/

#include"seven_segment.h"
#include <avr/io.h>
#include "../MCAL/gpio.h"
#include<util/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function to initialize the seven segment
 */
void SEVENSEGMENT_init(void)
{
	// Configure first 6 pins in PORTA as output pins
	int i;
	for(i =0; i<6;i++)
	{
		GPIO_setupPinDirection(SEVEN_SEGMENT_PORT_ID , (SEVEN_SEGMENT_PIN_ID  + i) , PIN_OUTPUT);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID, (SEVEN_SEGMENT_PIN_ID  + i), LOGIC_HIGH);
	}

	// Configure first 4 pins in PORTC as output pins
	for(i = 0; i<4; i++)
	{
		GPIO_setupPinDirection(SEVEN_SEGMENT_PORT1_ID, (SEVEN_SEGMENT_PIN1_ID + i) , PIN_OUTPUT);
		GPIO_writePin(SEVEN_SEGMENT_PORT1_ID, (SEVEN_SEGMENT_PIN1_ID  + i), LOGIC_LOW);

	}
}

/*
 * Description :
 * Function to Display on multiplexed seven segment simultaneously
 */
void SEVENSEGMENT_display(uint8 sec,uint8 minu,uint8 hour)
{
	PORTA = (PORTA & 0xC0) | 0x01;
	PORTC = (PORTC & 0xF0) | (sec %10);
	_delay_ms(3);

	PORTA = (PORTA & 0xC0) | 0x02;
	PORTC = (PORTC & 0xF0) | ((sec / 10) % 10);
	_delay_ms(3);

	PORTA = (PORTA & 0xC0) | 0x04;
	PORTC = (PORTC & 0xF0) | (minu % 10);
	_delay_ms(3);

	PORTA = (PORTA & 0xC0) | 0x08;
	PORTC = (PORTC & 0xF0) | ((minu / 10) % 10);
	_delay_ms(3);

	PORTA = (PORTA & 0xC0) | 0x10;
	PORTC = (PORTC & 0xF0) | (hour % 10);
	_delay_ms(3);

	PORTA = (PORTA & 0xC0) | 0x20;
	PORTC = (PORTC & 0xF0) | ((hour / 10) % 10);
	_delay_ms(3);

}
