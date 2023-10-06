/*
 * Buzzer.c
 *
 * Created: 05/09/2023 06:34:16 ص
 *  Author: user
 */ 
#include "Buzzer.h"
void Buzzer_Init(void){
	DDRD|=(1<<0);
	
}
void buzzer (void){
	int i;
	for(i=0;i<3;i++){
		PORTD |=(1<<0);
		_delay_ms(500);
		PORTD &=~(1<<0);
		_delay_ms(200);
	}
}