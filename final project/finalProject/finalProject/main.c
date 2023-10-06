#include <avr/interrupt.h>
#include "LCD.h"
#include "KEYPAD.h"
#include "temperature.h"
#include "IR.h"
#include "DCmotor.h"
#include "Buzzer.h"
#include "Hearbeat.h"
#include "servo.h"
#include "accelerometer.h"
#include "stopwatch.h"
int wrongPasscode;
uint8_t pulseCount=0;
uint8_t bpm=0;
uint8_t danger=0;  //if 10 times heat beat sensor gave critical reading then interrupt all programs 

int main(){
	//-------------Initializations-----------------------
	setupTimer();
	setupSensor();
	ADC_Init();
	stopWatch_Init();
	DCmotor_Init();
	IR_Init();
	Buzzer_Init();
	Temperature_Init();
	LCD_init();
	_delay_ms(4);
	KeyPadInit();
	_delay_ms(4);
	
	//-----------------------program----------------------
	while(1){
		if(IR_check()){
			wrongPasscode=0;
			LCD_cmd(0x0C);		//display on, cursor off
			_delay_ms(4);
			LCD_setCursor(0,0);
			LCD_writeStr("Hello There! ");
			_delay_ms(700);
			
			char passcode[5];
			bool isValid = false;
			
			while(IR_check()){
				
				LCD_clr();
				_delay_ms(2);
				LCD_writeStr("Enter PassCode!");
				
				LCD_setCursor(1,0);
				_delay_ms(10);
				
				// Get the four digits passcode
				uint8_t filled = fillArr((uint8_t*)passcode, 4);

				if (filled) {
					isValid = checkPasscode(passcode);

					if (isValid) {
						LCD_writeStr("  Correct");
						_delay_ms(1000);
						break;
					}
					else {
						LCD_writeStr("  Try Again");
						_delay_ms(1000);
						wrongPasscode++;
					}
				}
				else {
					LCD_writeStr("  Incomplete");
					_delay_ms(1000);
					wrongPasscode++;
				}
				if(wrongPasscode>=3)
						buzzer();
				_delay_ms(50);
				LCD_clrScnd(); // Clear display
				LCD_setCursor(1,0);
				}
				
				//------once passcode is correctly entered
				LCD_clr();
				_delay_ms(3);
				LCD_setCursor(0,0);
				
				char choice;
				while(IR_check()){ //as long as ir sensed you it displays options 
					LCD_Options();
					_delay_ms(20);
					while(IR_check()){
					choice=getChar();
					if(choice !='N') break;	
					}
					char exit;
					if(choice=='1'){ 	//temperature selected
						LCD_writeStr("1");
						_delay_ms(150);
						LCD_clr();
						LCD_setCursor(0,0);
						LCD_writeStr("Temperature= ");
						LCD_setCursor(1,0);
						LCD_writeStr("press 0 to Exit");
						
						while(IR_check()){ //while it senses you 
							exit=getChar();
							if(exit=='0'){
								OCR2=0; //close fan
								count=0; //to start fan of first speed not the speed we exit from
								 break; //close this mode if you pressed 0 (also close fan )
							}
							Temp_reading(); //in temperature.c
						}
						PORTA &= ~(1<<7); //disabling the en pin of dc motor
						
					}
					else if(choice=='2'){ //heartbeat rate selected
						
						while(IR_check()){
							exit=getChar();
							if(exit=='0') break;
							// Display BPM on LCD
							LCD_clr();
							_delay_ms(3);
							LCD_setCursor(0,0);
							LCD_writeStr("BPM = ");
							LCD_wriInt(bpm,0,6);
							LCD_setCursor(1,0);
							LCD_writeStr("press 0 to Exit ");
							_delay_ms(10);
						}
					}
					
					else if(choice=='3'){ //medication mode selected
						servo_init();
						_delay_ms(100);
						LCD_clr();
						_delay_ms(3);
						while(IR_check()){
							LCD_setCursor(0,0);
							OCR2 = 700; //makes servo angle=0 degree
							LCD_writeStr("Medication time?");
							LCD_setCursor(1,0);
							LCD_writeStr("0 = NO / 1 = YES");
							_delay_ms(10);
							exit=getChar();	
							if(exit=='0') break;
							while(exit=='1'){
								//if it is medication time
								OCR2 = 250; //makes servo angle=90 degrees
								_delay_ms(100);
								LCD_clr();
								LCD_setCursor(0,0);
								LCD_writeStr("Drawer Open !");
								LCD_setCursor(1,0);
								LCD_writeStr("Take your Bills !");
								_delay_ms(100);
								LCD_setCursor(1,0);
								LCD_writeStr("finish? hold = ");
								_delay_ms(200);
								if(getChar()=='='){
									OCR2 = 700; //makes servo angle=0 degree
									LCD_clr();
									LCD_setCursor(0,0);
									LCD_writeStr("Drawer closed!");
									LCD_setCursor(1,0);
									LCD_writeStr("with great Health!");
									_delay_ms(500);
									break;
								}
								
							}
							
						}
					}
					
					else if(choice=='4'){ //Distance selected
						int16_t  xRes=0,yRes=0,xOld=0,yOld=0;
						int distance=0;
						int try=0;
						while(IR_check()){
							exit=getChar();
							if(exit=='0') break;
							//units of x,y coordinates in g-forces
							xRes=ADC_Read(2); //x is connected to PA2
							yRes=ADC_Read(3); // y is connected to PA3

							// Convert ADC readings to centimeters
							xRes *= CALIBRATION_X_FACTOR;
							yRes *= CALIBRATION_Y_FACTOR;
							// Display distance on LCD
							DisplayCoordinates(xRes,yRes);
							
							_delay_ms(50);
							if(try>1){ //skip first 2 readings
									distance+=round(sqrt(pow((xRes-xOld),2)+pow((yRes-yOld),2)));
									LCD_clrScnd();
									LCD_setCursor(1,0);
									LCD_writeStr("dist= ");
									LCD_wriInt(distance,1,6);
									LCD_writeStr("cm");
									_delay_ms(100);
							}
							yOld=yRes;
							xOld=xRes;
							LCD_clrScnd();
							LCD_setCursor(1,0);
							LCD_writeStr("hold 0 to Exit");
							_delay_ms(50);
							try++;
						}
					}
					
					
					else if(choice=='5'){ //stop watch
						LCD_clr();
						LCD_clrfirst();
						LCD_setCursor(0,9);
						LCD_writeStr("o->Exit");
						LCD_setCursor(1,0);
						LCD_writeStr("1->stop/2->reset");
						start_stopWatch();
						while(IR_check()){
							displayTime();
							exit=getChar();
							if(exit=='0') {
								stop_stopWatch();
								seconds=0;
								minutes=0;
								hours=0;
								break;
							}
							else if (exit=='1') {
								stop_stopWatch();
								
								while(IR_check()){
									if(getChar()=='1'){
										start_stopWatch();
										break;
									}
								}
							}
							else if (exit=='2'){
								 reset_stopWatch();
								 LCD_clrfirst();
								 LCD_setCursor(0,9);
								 LCD_writeStr("o->Exit");
							}
						}
					}
					
					
					else if(choice=='6'){ //sleep monitoring selected
						int16_t  xRes=50,yRes=0,xOld=50,yOld=0; //xRes =50 means the human is initially slept in middle of the bed
						int distanceX=0;
						int distanceY=0;
						int turnedLeft=0;
						int turnedRight=0;
						int disturbed=0;
						int slept=1; //bec sleep mode is initiated when person is slept (initialized with 1 not 0)
						while(IR_check()){
							exit=getChar();
							if(exit=='0') break;
							
							// Display message on LCD
							LCD_clr();
							LCD_setCursor(0,0);
							LCD_writeStr("Sweet Dreams !");
							LCD_setCursor(1,0);
							LCD_writeStr("hold 0 if awaken");
							_delay_ms(500);
							
							//units of x,y coordinates in g-forces
							xRes=ADC_Read(2); //x is connected to PA2
							yRes=ADC_Read(3); // y is connected to PA3

							// Convert ADC readings to tens of cm
							xRes *= CALIBRATION_X_FACTOR*10;
							yRes *= CALIBRATION_Y_FACTOR*10;
							
							
							 
							if(xRes!=xOld||yRes!=yOld){
								//display his new position according to bed
								DisplayCoordinates(xRes,yRes);
								if(xRes>xOld){ //means he turned left while sleeping
									 turnedRight++;
									 LCD_clrfirst();
									 LCD_setCursor(0,0);
									 LCD_writeStr("you turned right");
									 _delay_ms(100);
									 LCD_clrfirst();
								}
								else if(xRes<xOld){
									 turnedLeft++;
									 LCD_clrfirst();
									 LCD_setCursor(0,0);
									 LCD_writeStr("you turned left");
									 _delay_ms(100);
								}
								if(yRes>yOld){
									if(disturbed<slept){ //so it doesnot count the distrubed times unless the person fell asleep before 
										 disturbed++;
										 LCD_clrfirst();
										 LCD_setCursor(0,0);
										 LCD_writeStr("Disturbed !");
										 _delay_ms(100);
									}
								}
								else if(yRes<yOld){
									if(disturbed==slept){ //so it dooesnot count the slept times unless the person was disturbed before
										slept++;
										LCD_clrfirst();
										LCD_setCursor(0,0);
										LCD_writeStr("fell back asleep!");
										_delay_ms(100);
									}
								}
							if(xRes>80||xRes<20){ //means he is about to fall off the bed
								LCD_clrfirst();
								LCD_setCursor(0,0);
								LCD_writeStr("about to FallOFF");
								buzzer(); // to awaken him
								_delay_ms(100);
								
							}
						}
						yOld=yRes;
						xOld=xRes;
					}
					//once he is up displays the sleep report
					LCD_clr();
					LCD_setCursor(0,0);
					LCD_writeStr("turned right");
					LCD_wriInt(turnedRight,0,13);
					LCD_writeStr("x");
					LCD_setCursor(1,0);
					LCD_writeStr("turned left");
					LCD_wriInt(turnedLeft,1,13);
					LCD_writeStr("x");
					_delay_ms(300);
					LCD_clr();
					LCD_setCursor(0,0);
					LCD_writeStr("disturbed ");
					LCD_wriInt(disturbed,0,10);
					LCD_writeStr("x");
					_delay_ms(300);
				}
					
					
				else if(choice=='7'){ //re-displaying the menu
					continue;
				}
			}
		}
				
		else {
			LCD_cmd(0x08);	//if ir sensed no one it closes the lcd
			_delay_ms(2);
		}
	}
		
	
	return 0;
}

//-----------------Interrupt Service Routines-------------------

// Interrupt service routine for heartbeat sensor
ISR(INT0_vect)
{
	pulseCount++;
	
	if((bpm>100||bpm<60)&&(bpm!=0)){
		danger++;
	}
	else
	danger=0;
	 
}

// Interrupt service routine for Timer1 compare match
ISR(TIMER1_COMPA_vect)
{
	 // Calculate BPM after the specified time interval
	 static uint8_t intervalCounter = 0;
	 intervalCounter++;
	 if (intervalCounter >= MEASURE_INTERVAL)
	 {
		 calculateBPM();
		 intervalCounter = 0;
		 
	 }
	
	if(danger>2){ //critical heart rate for some time
		emergency();
		}
		
}

// Interrupt service routine for Timer0 Normal mode to count seconds,minutes,hours
ISR(TIMER0_OVF_vect){
	// Increment seconds
	seconds++;
	
	// Check if a minute has passed
	if (seconds == 60) {
		seconds = 0;
		minutes++;
		
		// Check if an hour has passed
		if (minutes == 60) {
			minutes = 0;
			hours++;
		}
	}
}