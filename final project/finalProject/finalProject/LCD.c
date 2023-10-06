#include "LCD.h"
void LCD_data(char c){
	LCD_DATA=c;             //LCD_DATA is connected to port A, //RS,RW,EN is selected to be pin4,5,6 port D
	PORTD |= (1<<RS);		//in writing reset is enabled
	PORTD &= ~(1<<RW);
	PORTD |= (1<<EN);
	_delay_ms(5);
	PORTD &= ~(1<<EN);
}


void LCD_cmd(uint8_t command){
	LCD_DATA =command;
	PORTD &= ~(1<<RS);		//rs,rw disabled / EN is enabled then disabled
	PORTD &= ~(1<<RW);
	PORTD |= (1<<EN);
	_delay_ms(5);
	PORTD &= ~(1<<EN);
}

void LCD_init(void){
	_delay_ms(15);          //needs time for tw
	DDRB = 0xff;		    //port A which is lcd data port is output
	DDRD |= 0x70;		    //port D (4,5,6) which is lcd command port is output
	LCD_cmd(0x38);		    //using 2lines 8bit mode
	_delay_ms(5);
	LCD_cmd(0x01);		    //clear the lcd screen
	_delay_ms(5);
	LCD_cmd(0x02);			//return home
	_delay_ms(5);
	LCD_cmd(0x06);			//cursor increment
	_delay_ms(5);
	LCD_cmd(0x80);			//move cursor to the beginning of first line
	_delay_ms(5);
}

void LCD_setCursor(uint8_t x,uint8_t y){
	uint8_t adress=0;
	if(x==0)
	adress=0x80;

	else if(x==1)
	adress=0xC0;

	if(y<16)
	adress+=y;

	LCD_cmd(adress);
}


void LCD_clr(void){
	LCD_cmd(0x01);
	_delay_ms(5);
}

void LCD_clrScnd(void){
	LCD_cmd(0xC0);
	_delay_ms(1);
	uint8_t i;
	for(i=0xC0;i<=0xCF;i++){
		LCD_data(' ');
	}
}

void LCD_clrfirst(void){
	LCD_cmd(0x80);
	_delay_ms(1);
	uint8_t i;
	for(i=0xC0;i<=0xCF;i++){
		LCD_data(' ');
	}
}

void LCD_writeStr(char *a){
	// Iterate over each character in the string
	while (*a) {
		LCD_data(*a);
		_delay_ms(1);
		a++;
	}
}


void LCD_Options(void){
	LCD_clr();
	_delay_ms(3);
	LCD_setCursor(0,0);
	_delay_ms(2);
	LCD_writeStr("Choose Mode: ");
	LCD_setCursor(1,0);
	LCD_writeStr("1) Temperature ");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
	LCD_writeStr("2)Heartbeat Rate");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
	LCD_writeStr("3) Medication ");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
	LCD_writeStr("4) Distance ");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
	LCD_writeStr("5) Stop Watch ");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
	LCD_writeStr("6) Sleep Monitoring ");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
	LCD_writeStr("7) Retry ");
	_delay_ms(500);
	LCD_clrScnd();
	_delay_ms(200);
	LCD_setCursor(1,0);
}

void LCD_wriInt(int num,int x,int y)
{
	char buffer[10];  // Buffer to hold the string representation of the integer
	itoa(num, buffer, 10);  // Convert the integer to a string
	LCD_setCursor(x,y);
	LCD_writeStr(buffer);
}

void emergency(void){
	LCD_clr();
	LCD_writeStr("BPM = ");
	LCD_wriInt(bpm,0,6);
	_delay_ms(100);
	LCD_clr();
	LCD_setCursor(0,0);
	LCD_writeStr("BloodType: O+");
	LCD_setCursor(1,0);
	LCD_writeStr("01279707819");
	buzzer();
	_delay_ms(300);
}