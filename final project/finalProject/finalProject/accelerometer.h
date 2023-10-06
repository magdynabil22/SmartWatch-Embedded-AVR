/*
 * accelerometer.h
 *
 * Created: 10/09/2023 01:54:30 ص
 *  Author: user
 */ 


#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <avr/delay.h>
#include <avr/io.h>
#include "LCD.h"
#define CALIBRATION_X_FACTOR 0.1/128  // Conversion factor for X-axis readings (cm per ADC unit)
#define CALIBRATION_Y_FACTOR 0.1/128  // Conversion factor for Y-axis readings (cm per ADC unit)

void ADC_Init();
uint16_t ADC_Read(uint8_t channel);
void DisplayCoordinates(int16_t x, int16_t y);

#endif /* ACCELEROMETER_H_ */