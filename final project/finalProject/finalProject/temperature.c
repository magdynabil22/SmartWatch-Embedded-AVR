#include "temperature.h"
void Temperature_Init(void){
    DDRA &= ~(1<<0);
    ADCSRA = 0x87; //enabling adc and setting prescalar to 128
	ADMUX = 0xE0; //Internal 2.56V Voltage Reference ,  left adjust the result , selecting ADC0
}
void convertNdisplayTemp(unsigned char value){ //convert int to char 
	//converting int to char
	unsigned char d1,d2;
	d1=value/10;
	d2=value%10; 
	LCD_cmd(0x8D); //move cursor to after Temperature= " " 
	LCD_data(d1+0x30); //to display the first temperature digit as char (Ascii of 3 is 33, ascii of 5 is 35)
	LCD_data(d2+0x30); //to display the second temperature digit as char (Ascii of 3 is 33, ascii of 5 is 35)
}
void Temp_reading(void){
		ADCSRA |= (1<<6); //start conversion
		while(ADCSRA & (1<<ADIF)); //wait until finishing conversion
		int data = ADCH;
		convertNdisplayTemp (data);
		if((data>35)){
			LCD_clrScnd();
			LCD_setCursor(1,0);
			LCD_writeStr("Fan ON/0 to Exit");
			Fan_ON(); //fan is on once temp exceeds 35 degree celsius and this function is in Dcmotor.c 
		} 
		else {
			
			LCD_clrScnd();
			LCD_setCursor(1,0);
			LCD_writeStr("FanOFF/0 to Exit");
		}
}