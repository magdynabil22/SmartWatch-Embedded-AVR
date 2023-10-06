/*
 * stopwatch.c
 *
 * Created: 10/09/2023 01:13:42 م
 *  Author: user
 */ 
#include "stopwatch.h"
uint8_t seconds=0;
uint8_t minutes=0;
uint8_t hours=0;
void stopWatch_Init(void){
	
	 TCNT0 =0;
	 TCCR0 &= ~((1<<WGM00)|(1<<WGM01)|(1<<COM00)|(1<<COM01)); //normal mode wit oc0 disconnected
	 // Enable Timer 0 overflow interrupt
	 TIMSK |= (1 << TOIE0);
	 
	 // Enable global interrupts
	 sei();
}



void start_stopWatch(void){
	//setting 1024 prescalar
	TCCR0 |= (1<<CS00)|(1<<CS02);
	TCCR0 &= ~(1<<CS01);
}

void stop_stopWatch(void){
	TCCR0 &= ~((1<<CS01)|(1<<CS00)|(1<<CS02)); //turn off counter
}

void reset_stopWatch(void){
	seconds=0;
	minutes=0;
	hours=0;
	TCCR0 |= (1<<CS00)|(1<<CS02);
	TCCR0 &= ~(1<<CS01); //turn ON counter
}

void displayTime(void){
	LCD_setCursor(0,0);
	LCD_wriInt(hours,0,0);
	LCD_writeStr(":");
	LCD_wriInt(minutes,0,3);
	LCD_writeStr(":");
	LCD_wriInt(seconds,0,6);
}


