#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include "keypad.h"
#include "lcd.h"
#include <avr/eeprom.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BRC ((F_CPU/16/BAUDRATE)-1)


void savePIN(void);

//Porque o ultimo caracter tem que ser null
char code[5];

int main()
{
	// Initialize LCD display
	lcd_init(LCD_DISP_ON);
	
	//Configura as portas para o Keypad
	configKeypad();

	//Configura o rele
	DDRC |= (1<<PORTC0);


	savePIN();
	
	// LER O CODIGO GUARDADO NA EEPROM
	uint16_t data;
	data = eeprom_read_word((uint16_t*) 1246);
	
	//GUARDA O CODIGO NA VARIAVEL CODE
	sprintf(code,"%d",data);
	


	
	while(1)
	{
		    //LIMPA ECRA
			lcd_clrscr();
			//POSICAO DE ESCRITA
			lcd_gotoxy(3, 0);
			//ESCREVE NO ECRA
			lcd_puts("CODE");

			lcd_gotoxy(6,1);
			lcd_puts("----");
		
		char pin[5];
		int i = 0;
		int l = 6;
		
		//ESPERAR QUE DIGITE O CODIGO
		while(i!=4){
		
		char key = keyPressed();
		
			if(key != 'N'){
				pin[i] = key;
				lcd_gotoxy(l,1);
				lcd_putc('*');
				i++;
				l++;
			}
		}
		
		pin[4] = NULL;
		code[4] = NULL;
		if(strcmp(code,pin) == 0){
			//Success
			lcd_clrscr();
			lcd_gotoxy(1,0);
			lcd_puts("OPENED!!!");
			
			//ESPERA 3 SEGUNDOS E TRANCA DE NOVO

			PORTC |= (1<<PORTC0);
			TCCR1B |= (1<<CS10) | (1<<CS12);
			OCR1A = 46875;// fui calculador para ter 3 segundos esse e codico 46875
			TCNT1 = 0;
				
			//Locker timeout
			while((TIFR1 & (1<<OCF1A)) == 0);// wait till the timer overflow flag is SET
			PORTC ^= (1<< PORTC0);
			TCNT1 = 0;
			TCCR1B = 0X00;

			TIFR1 |= (1<<OCF1A) ; //clear timer1 overflow flag
			lcd_clrscr();
		}else{
			//Fail
			lcd_clrscr();
			lcd_gotoxy(1,0);
			lcd_puts("WRONG CODE!!!");
			_delay_ms(500);

		}
		

		

		
		//UDR0=key;
		
	}
	return 0;

}

void savePIN(void){
	//End. de memória onde está guardado o pin
	uint16_t data = 1246;
	
	char buf[4];
	char response[4];
	
	//Ler o pino guardado
	data = eeprom_read_word((uint16_t*) 1246);
	//Transformar o pin guardado em string o int status dá o numero de caracteres guardado
	int status = sprintf(buf,"%d",data);
	//Transformar o status em string
	sprintf(response,"%d",status);
	
	//Caso seja diferente de 4 entao guardar um novo codigo
	if(status != 4){
		
		//IMPRIME PARA O ECRA
		lcd_gotoxy(3, 0);
		lcd_puts("SAVE CODE");

		lcd_gotoxy(6,1);
		lcd_puts("----");
		
		//LER DO TECLADO
		int i = 0;
		char pin[4]={'-','-','-','-'};
		while(i<4){
			
			//LER TECLADO E COLOCAR UM NOVO
			char key = keyPressed();
			if(key != 'N'){
				pin[i] = key;
				lcd_gotoxy(6,1);
				lcd_puts(pin);
				i++;
			}
		}
		
		//Time for reading last number input
		_delay_ms(500);
		
		//Guardar o novo codigo
		eeprom_write_word((uint16_t*) 1246,atoi(pin));
		

	}

}