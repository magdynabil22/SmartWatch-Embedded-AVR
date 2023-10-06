/*
 * servo.c
 *
 * Created: 09/09/2023 10:47:26 م
 *  Author: user
 */ 
#include "servo.h"

// Function to initialize the servo motor
void servo_init()
{
	//enabling servo and disabling dc motor 
	DDRA |= (1<<7)|(1<<6);
	PORTA |= (1<<6);
	PORTA &= ~(1<<7);

	// Configure Timer2 in Fast PWM mode
	TCCR2 |= (1 << WGM20) | (1 << WGM21);

	// Set non-inverted mode for OC2
	TCCR2 |= (1 << COM21);

	// Set prescaler to 8
	TCCR2 |= (1 << CS21);

	// Set the initial position of the servo to 0 degrees
	OCR2 = 700;
	_delay_ms(50); // Wait for the servo to reach the initial position
}


