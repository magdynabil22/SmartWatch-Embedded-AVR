

#ifndef KEYPAD_H_
#define KEYPAD_H_
/*
#include <avr/delay.h>
#include <avr/io.h>*/
#include "LCD.h"
#include <stdbool.h>
#include <util/delay.h>

#define KEYPAD_DDR DDRC
#define KEYPAD_PORT PORTC
#define KEYPAD_PIN PINC

void KeyPadInit();//initiation of port direction
char getChar();//return the character that the user pushed
uint8_t fillArr(uint8_t *a,uint8_t max);//pass a string a its size to fill it with user inputs
//returns 1 if filled successfully and return 0 if user pressed back and the array wasnt fully filled
bool checkPasscode(char passcode[]);

#endif /* KEYPAD_H_ */
