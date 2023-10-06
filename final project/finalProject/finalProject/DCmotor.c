/*
 * DCmotor.c
 *
 * Created: 05/09/2023 01:54:47 ص
 *  Author: user
 */ 
#include "DCmotor.h"
#include "KEYPAD.h"
void DCmotor_Init(void){
	TCNT2=0;
	// Configure Timer2 for PWM generation
	TCCR2 |= (1 << WGM20) | (1 << WGM21);  // Fast PWM mode
	TCCR2 |= (1 << COM21);                 // Set at non-inverting mode
	TCCR2 &= ~((1<<4)|(1<<2));
	DDRD |= (1<<7); //making oc2 output 
	DDRD &= ~(1<<3); //push button for selecting the speed of fan
	PORTD |= (1<<3); //enabling pull up resistor
	
	//enabling the EN pin of dc motor
	DDRA |= (1<<7);
	PORTA |= (1<<7);
}

count=0;
void Fan_ON (void){
	//enabling the EN pin of dc motor and disablng servo
	DDRA |= (1<<7)|(1<<6);
	PORTA |= (1<<7);
	
	TCCR2 |= (1 << CS20) | (1 << CS21);    // Prescaler 64 (to start timer)
	if(!(PIND&0x08)){
			while(!(PIND&0x08)); //wait until button is unpressed
			LCD_clrScnd();
			LCD_setCursor(1,0);
			count++;
			switch(count){
				case 1: 
					LCD_writeStr("first speed");
					OCR2=64;
					break;
				case 2:
					LCD_writeStr("second speed");
					OCR2 = 128;
					break;
				case 3:
					LCD_writeStr("third speed");
					OCR2 = 255;
					break;
				default:
					LCD_writeStr("No speed");
					OCR2=0;
					count=0;
			     }
		}
	}