/*
ATtiny 25/45/85 DIP8
PTT IN -> PIN REST
PTT OUT -> PINOVI 5,6,7,3,2 /* in that order

IF PTT IS PRESSED WHILE BOOTING DELAY EQUALS 100ms, else 30 MS (for VHF and HF purposes)

LED BLINKS TWIC OR 3 TIME IF 30 or 100 ms SELECTED (LED 1)


DELAY FROM:
https://github.com/johnmccombs/arduino-libraries/blob/master/glcd/include/delay.h

Mirko 9a6kx 2018

*/

#include <avr/io.h>
#include <util/delay.h>


int main(void){

int delay;
int pressed = 0;
int changed = 0;

DDRB |= (1 << PINB0);
DDRB |= (1 << PINB1);
DDRB |= (1 << PINB2);
DDRB |= (1 << PINB3);
DDRB |= (1 << PINB4);
DDRD &= ~(1 << PIND5);

if (bit_is_clear(PIND,5)){
delay = 100;
	for (int i=0; i<6; i++){
	PORTB ^= (1<<PINB0);
	_delay_ms(300);
	}
}
else{
delay = 30;
	for (int i=0; i<4; i++){
	PORTB ^= (1<<PINB0);
	_delay_ms(300);
	}
}

_delay_ms(3000);

while(1)
	{
		if(bit_is_clear(PIND,5)){
			if (pressed == 1)
			{
				changed = 0;
			}
			else
			{
				pressed = 1;
				changed = 1;
			}
		}
		else
			{
			if (pressed == 0)
			{
				changed = 0;
			}
			else
			{
				pressed = 0;
				changed = 1;
			}
		}

	if (changed == 1)
	{
		if(pressed == 1)
		{
		PORTB |= (1 << PINB0);
		_delay_ms(delay);
		PORTB |= (1 << PINB1);
		_delay_ms(delay);
		PORTB |= (1 << PINB2);
		_delay_ms(delay);
		PORTB |= (1 << PINB3);
		_delay_ms(delay);
		PORTB |= (1 << PINB4);
		_delay_ms(delay);
		}
		if(pressed == 0)
		{
		PORTB &= ~(1 << PINB0);
		_delay_ms(delay);
		PORTB &= ~(1 << PINB1);
		_delay_ms(delay);
		PORTB &= ~(1 << PINB2);
		_delay_ms(delay);
		PORTB &= ~(1 << PINB3);
		_delay_ms(delay);
		PORTB &= ~(1 << PINB4);
		_delay_ms(delay);
		}

	
	}
	
	}


}