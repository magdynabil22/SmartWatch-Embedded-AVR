/*
 * Hearbeat.h
 *
 * Created: 05/09/2023 10:09:51 م
 *  Author: user
 */ 


#ifndef HEARBEAT_H_
#define HEARBEAT_H_

#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define PRESCALER 64  
#define SENSOR_PIN PD2 
#define MEASURE_INTERVAL 2 // Time interval in seconds for measuring BPM

uint8_t pulseCount ;
uint8_t bpm ;
uint8_t danger;
void setupTimer(void);
void setupSensor(void);
void calculateBPM(void);

#endif /* HEARBEAT_H_ */