/******************************************************************************
 *
 * Module: 7_segment
 *
 * File Name: seven_segment.h
 *
 * Description: header file for the Multiplexed seven segment
 *
 * Author: Omar Muhammad
 *
 *******************************************************************************/


#ifndef HAL_SEVEN_SEGMENT_H_
#define HAL_SEVEN_SEGMENT_H_

#include "../MCAL/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Seven-segment HW Ports and Pins Ids */
#define SEVEN_SEGMENT_PORT_ID                 PORTA_ID
#define SEVEN_SEGMENT_PIN_ID                  PIN0_ID
#define SEVEN_SEGMENT_PORT1_ID                PORTC_ID
#define SEVEN_SEGMENT_PIN1_ID                 PIN0_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function to initialize the seven segment
 */
void SEVENSEGMENT_init(void);

/*
 * Description :
 * Function to Display on multiplexed seven segment simultaneously
 */
void SEVENSEGMENT_display(uint8 sec,uint8 minu,uint8 hour);

#endif /* HAL_SEVEN_SEGMENT_H_ */
