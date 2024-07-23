/*
 * Lab2.c
 *
 * Created: 17/07/2024 17:14:09
 * Author : luisa
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "ADC/ADC.h"
#include "LCD8/LCD8.h"
#include "UART/UART0.h"

volatile uint8_t POT1 = 0; 
volatile uint8_t POT2 = 0; 
volatile uint8_t Turno = 0;
volatile int8_t contador = 0; 

char lista[10] = {'0','1','2','3','4','5','6','7','8','9'};
char lista1[4], lista2[4], lista3[4] = {'0', '0', '0'};
char contadorStr[4];

void setup(void);
void initTimer0(void);
void newLista(char *lista, int valor);
void contadorToStr(char *str, int8_t valor); 


int main(void)
{
    setup();
	initLCD8bit();
	initTimer0();
	SetupUART0(M9600);
	
	LCD_Set_Cursor(1,1);
	LCD_Write_String("S1");
	
	
	LCD_Set_Cursor(6,1);
	LCD_Write_String("S2");
	
	LCD_Set_Cursor(11, 1);
	LCD_Write_String("S3");
	
    while (1) 
    {
		newLista(lista1, POT1);
		newLista(lista2, POT2); 
		newLista(lista3, 255);
		contadorToStr(contadorStr, contador); 
		
		LCD_Set_Cursor(1,2);
		LCD_Write_String(lista1);
		LCD_Set_Cursor(6, 2);
		LCD_Write_String(lista2);
		
		LCD_Set_Cursor(11, 2);
		LCD_Write_String(contadorStr);
		  
		_delay_ms(50);
    }
}

void setup(void){
	cli();
	SetupADC(PC5);
	SetupADC(PC6);
	sei();
}

void initTimer0(void){
	TCCR0B |= (1<<CS00)|(1<<CS02);
	TCNT0 = 220;
	TIMSK0 |= (1<<TOIE0);
}

void newLista(char *lista, int valor) {
	lista[0] = '0' + (valor / 100);
	lista[1] = '0' + ((valor / 10) % 10);
	lista[2] = '0' + (valor % 10);
	lista[3] = '\0';
}

void contadorToStr(char *str, int8_t valor) {
	int is_negative = 0;
	if (valor < 0) {
		is_negative = 1;
		valor = -valor;
	}

	if (is_negative) {
		str[0] = '-';
		str[1] = '0' + (valor / 10);
		str[2] = '0' + (valor % 10);
		str[3] = '\0';
		} else {
		str[0] = '0' + (valor / 10);
		str[1] = '0' + (valor % 10);
		str[2] = '\0';
	}
}

ISR(ADC_vect){
	switch(Turno){
		case 0:
			POT1 = ADCH; 
			break;
		case 1:
			POT2 = ADCH; 
			break;
		default:
			break;
	}
	ADCSRA |= (1<<ADIF);
}

ISR(TIMER0_OVF_vect){
	switch(Turno){
		case 0:
			Turno = 1;
			ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)); //PC5
			ADMUX|=(1<<MUX2)|(1<<MUX0);
			break;
		case 1:
			Turno = 0; 
			ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));
			ADMUX|=(1<<MUX2)|(1<<MUX1);
			break;		
	}
	ADCSRA |= (1<<ADSC);
	//TCNT0 = 250;
	TCNT0 = 220;
	TIFR0 |= (1 << TOV0);
}

ISR(USART_RX_vect){
	uint8_t dato = UDR0;  // Leer el dato recibido (para limpiar la bandera de interrupción)
	if (dato == 'a') {
		contador++;       // Incrementar el contador si el dato es 'a'
		} else if (dato == 'b') {
		contador--;       // Decrementar el contador si el dato es 'b'
	}
}