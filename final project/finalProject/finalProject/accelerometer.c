/*
 * accelerometer.c
 *
 * Created: 10/09/2023 01:54:13 ص
 *  Author: user
 */ 
#include "accelerometer.h"

void ADC_Init() {
	// Set PA2, PA3, and PA4 as input
	DDRA &= ~((1 << PA2) | (1 << PA3) | (1 << PA4));

	// Enable ADC, set ADC prescaler to 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
	// Set ADC channel
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);

	// Start ADC conversion
	ADCSRA |= (1 << ADSC);

	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Return ADC value
	return ADC;
}

void DisplayCoordinates(int16_t x, int16_t y) {
	LCD_clr();
	LCD_setCursor(0,0);
	LCD_writeStr("X: ");
	LCD_wriInt(x,0,2);
	LCD_setCursor(0,8);
	LCD_writeStr(" Y:");
	LCD_wriInt(y,0,11);
}
	
