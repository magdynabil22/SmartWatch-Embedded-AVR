/*
 * DCmotor.h
 *
 * Created: 05/09/2023 01:55:08 ص
 *  Author: user
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include <avr/delay.h>
#include <avr/io.h>
void DCmotor_Init(void);
void ventilation (void);
int count;

#endif /* DCMOTOR_H_ */