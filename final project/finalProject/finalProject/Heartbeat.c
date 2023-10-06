/*
 * Heartbeat.c
 *
 * Created: 05/09/2023 10:09:33 م
 *  Author: user
 */ 
#include "Hearbeat.h"
#include "LCD.h"


void setupTimer()
{
	// Set Timer1 to CTC mode with prescaler = 64
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

	// Set compare match value for 1Hz frequency
	OCR1A = (F_CPU / (PRESCALER * 1)) - 1;

	// Enable Timer1 compare interrupt
	TIMSK |= (1 << OCIE1A);

	// Enable global interrupts
	sei();
}

void setupSensor()
{
	// Configure sensor pin as input
	DDRD &= ~(1 << SENSOR_PIN);

	// Enable internal pull-up resistor for sensor pin
	PORTD |= (1 << SENSOR_PIN);

	// Enable external interrupt INT0
	GICR |= (1 << INT0);

	// Set interrupt on falling edge
	MCUCR |= (1 << ISC01);
}

void calculateBPM(void)
{
	  // Calculate BPM using pulse count and time interval
	  bpm = (pulseCount * 60) / MEASURE_INTERVAL;

	  // Reset pulse count
	  pulseCount = 0;
	 
}