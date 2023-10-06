/*
 * stopwatch.h
 *
 * Created: 10/09/2023 01:14:05 م
 *  Author: user
 */ 


#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <avr/delay.h>
#include <avr/io.h>
#include "LCD.h"
#include "KEYPAD.h"

uint8_t seconds;
uint8_t minutes;
uint8_t hours;

void stopWatch_Init(void);
void start_stopWatch(void);
void stop_stopWatch(void);
void reset_stopWatch(void);
void displayTime(void);

#endif /* STOPWATCH_H_ */