#include "KEYPAD.h"
void KeyPadInit(){
	KEYPAD_DDR =0xF0;
	KEYPAD_PORT = 0x00;
}

char getChar(){

		KEYPAD_PORT=0x10;
		if(KEYPAD_PIN&0x01){while(KEYPAD_PIN&0x01) {} return'7'; }
		else if(KEYPAD_PIN&0x02){while(KEYPAD_PIN&0x02) {} return '4'; }
		else if(KEYPAD_PIN&0x04){while(KEYPAD_PIN&0x04) {} return '1'; }
		else if(KEYPAD_PIN&0x08){while(KEYPAD_PIN&0x08) {} return 'c'; }
		_delay_ms(5);

		KEYPAD_PORT=0x20;
		if(KEYPAD_PIN&0x01){while(KEYPAD_PIN&0x01) {} return '8'; }
		if(KEYPAD_PIN&0x02){while(KEYPAD_PIN&0x02) {} return '5'; }
		if(KEYPAD_PIN&0x04){while(KEYPAD_PIN&0x04) {} return '2'; }
		if(KEYPAD_PIN&0x08){while(KEYPAD_PIN&0x08) {} return '0'; }
		_delay_ms(5);

		KEYPAD_PORT=0x40;
		if(KEYPAD_PIN&0x01){while(KEYPAD_PIN&0x01) {} return '9'; }
		if(KEYPAD_PIN&0x02){while(KEYPAD_PIN&0x02) {} return '6'; }
		if(KEYPAD_PIN&0x04){while(KEYPAD_PIN&0x04) {} return '3'; }
		if(KEYPAD_PIN&0x08){while(KEYPAD_PIN&0x08) {} return '='; }
		_delay_ms(5);

		KEYPAD_PORT=0x80;
		if(KEYPAD_PIN&0x01){while(KEYPAD_PIN&0x01) {} return'/'; }
		if(KEYPAD_PIN&0x02){while(KEYPAD_PIN&0x02) {} return 'x'; }
		if(KEYPAD_PIN&0x04){while(KEYPAD_PIN&0x04) {} return '-'; }
		if(KEYPAD_PIN&0x08){while(KEYPAD_PIN&0x08) {} return '+'; }
		_delay_ms(5);


return 'N';

}

uint8_t fillArr(uint8_t *a, uint8_t max) {
	uint8_t count = 0;

	while ((count < max)&&IR_check()) { //if ir stops sensing you the lcd turn off
		char key = getChar();
		if (key != 'N') {
			LCD_data(key);
			_delay_ms(10);
			a[count] = key;
			_delay_ms(10);

		// Check if user pressed =
		if (a[count] == '=') {
			return 0;
		}

		count++;
		}
	}

	return 1;

}

bool checkPasscode(char passcode[]) {
	char valid[4]="1234";
	bool equal=true;
	uint8_t i;
	for(i=0;i<4;i++){
		if(passcode[i]!=valid[i]) {equal=false;break;}
	}
	return equal;
}
