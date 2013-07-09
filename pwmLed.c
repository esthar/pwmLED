/*
 * pwmLed.c
 *
 * Created: 10/26/2012 17:30:03
 *  Author: Andre Lucas
 PWM LED on PD6 - OCR0A
 */ 

#define F_CPU 1000000 //Define the clock rate of the uC, which is needed by some dependencies like delay.h

#include <avr/io.h>		//Include Input Output pins library e.g. DDRB and PORTB and PINB registers
#include <util/delay.h>	//Delay functions _delay_ms(miliseconds) and _delay_(microseconds) which puts the IC into an idle calculation for that specific amount of time. (It is basically a for loop counting nothing relevant)
#include "sinelookup.h" //Generated sinusoidal table

void init(void);

int main(void){
	
	init();
	
	while(1){
		for (char i=0; i<255; i++){
			
			OCR0A = 255 - (sine[i]); //We start with the LED completely off, duty cycle set to 0% and iterate the sine loop until it's fully on.
			_delay_ms(10);
		}
		
		for (char i=0; i<255; i++){
			
			OCR0A = 0 + (sine[i]); //Then we do the reverse by turning off the LED.
			_delay_ms(10);
			
		}
	}
}

void init(void){
	DDRD = 1<<6;	//Define the pin D6 to be an output. See datasheet to understand DDRx, PORTx and PINx registers.  1<<0 is same as 0b0000001
	
	TCCR0A |= (1 << COM0A1); //Set none-inverting mode

	TCCR0A |= (1 << WGM01) | (1 << WGM00); //Set fast PWM Mode

	TCCR0B |= (1 << CS01); //Set prescaler to 8 (PWM Clock = Main Clock/8) and starts PWM
	
	OCR0A = 255; //0CR0A is the duty cycle 255 in this case is 0% duty cycle.
	
	}
	


