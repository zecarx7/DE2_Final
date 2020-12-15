/*
 * keypad.c
 *
 * Created: 29/11/2020 19:31:10
 *  Author: JoseAfonso
 */ 

#define  F_CPU 16000000
#include <avr/io.h>
#include "keypad.h"
#include <util/delay.h>


void configKeypad(){
		DDRB |= 0b00000111; //Set rows as outputs and cols as inputs
}

uint8_t keyPressed(){
	while(1){
	for(int col=0;col<3;col++){
		PORTB |= (1<<col);
		_delay_ms(50);
		if(PINB & (1 << PINB3)){ 
			if(col==0){
			
	            while(PINB & (1 << PINB3));
					PORTB &= ~(1<<col);
				return 'N'; 
				
			}
			if(col==1){
				
	            while(PINB & (1 << PINB3));
				PORTB &= ~(1<<col);
				return '0';
			}
			if(col==2){
		
	        while(PINB & (1 << PINB3));
				PORTB &= ~(1<<col);
				return 'N';
			}
		}
		if(PINB & (1 << PINB4)){
			if(col==0){
	while(PINB & (1 << PINB4));
	PORTB &= ~(1<<col);
				return '7';
			}
			if(col==1){
						while(PINB & (1 << PINB4));
						PORTB &= ~(1<<col);
				return '8';
			}
			if(col==2){		
				while(PINB & (1 << PINB4));
				PORTB &= ~(1<<col);
				return '9';
			}
		}
		if(PINB & (1 << PINB5)){
			if(col==0){
					while(PINB & (1 << PINB5));
					PORTB &= ~(1<<col);
				return '4';
			}
			if(col==1){
						while(PINB & (1 << PINB5));
						PORTB &= ~(1<<col);
				return '5';
			}
			if(col==2){
						while(PINB & (1 << PINB5));
						PORTB &= ~(1<<col);
				return '6';
			}
		}
		if(PINB & (1 << PINB6)){
			if(col==0){
						while(PINB & (1 << PINB6));
						PORTB &= ~(1<<col);
				return '1';
			}
			if(col==1){
						while(PINB & (1 << PINB6));
						PORTB &= ~(1<<col);
				return '2';
			}
			if(col==2){
				while(PINB & (1 << PINB6));
				PORTB &= ~(1<<col);
				return '3';
			}
		}
		
		PORTB &= ~(1<<col);
	}
	_delay_ms(50);
	}
	
}



