/*
 * IR.c
 *
 * Created: 05/09/2023 04:44:27 ص
 *  Author: user
 */ 
#include "IR.h"
void IR_Init(void){
	DDRD &=~ (1<<1);
	PORTD |= (1<<1);
}
bool IR_check(void){
	return (PIND&0x02);
}