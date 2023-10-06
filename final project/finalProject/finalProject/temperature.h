#ifndef temperature_H_
#define temprature_H_
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "LCD.h"
#include "DCmotor.h"
void Temperature_Init(void);
void convertNdisplay(unsigned char value);
void Temp_reading(void);
#endif
