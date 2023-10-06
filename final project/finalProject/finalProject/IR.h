/*
 * IR.h
 *
 * Created: 05/09/2023 04:44:56 ص
 *  Author: user
 */ 


#ifndef IR_H_
#define IR_H_
#include <avr/delay.h>
#include <avr/io.h>
#include <stdbool.h>
void IR_Init(void);
bool IR_check(void);


#endif /* IR_H_ */