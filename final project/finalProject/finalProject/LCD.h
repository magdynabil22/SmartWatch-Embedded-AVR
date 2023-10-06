/*
 * LCD.h
 *
 * Created: 8/19/2023 11:31:17 AM
 *  Author: omart
 */


#ifndef LCD_H_
#define LCD_H_
#include <stdio.h>
#include <stdlib.h>
#include <avr/delay.h>
#include <avr/io.h>
#include "Hearbeat.h"

#define LCD_DATA PORTB		//port B is selected to be data port
#define RS PD4				//reset is selected to be pin4 port D
#define RW PD5				//readwrite is selected to be pin5 port D
#define EN PD6				//enable is selected to be pin6 port D

void LCD_data(char c);//sends a data (char) to the lcd to be displayed
void LCD_cmd(uint8_t command);//sends a command to the lcd
void LCD_init(void);//initiation of ports direction and initiation of lcd
void LCD_setCursor(uint8_t x,uint8_t y);//moves currsor to any position //x = col,y=row //// 0 ---> first row or first col
void LCD_clr(void);
void LCD_clrScnd(void);//clears the second line of the lcd only and set cursor to the beginning of the second line
void LCD_clrfirst(void);//clears the first line of the lcd only and set cursor to the beginning of the first line
void LCD_writeStr(char *a);//displays entire string on the lcd
void LCD_Options(void);
void LCD_wriInt(int num,int x,int y);
void emergency(void);


#endif /* LCD_H_ */
