/*
 * UART0.c
 *
 * Created: 18/07/2024 13:13:41
 *  Author: luisa
 */ 
#include "UART0.h"

void SetupUART0(uint8_t MODO)
{
	if (MODO == M9600){
		//Paso 1: RX como entrada y TX como salida
		DDRD &= ~(1<<DDD0);
		DDRD |= (1<<DDD1);
		
		//Paso 2: Confi. UCSR0A
		UCSR0A = 0;
		
		//Paso 3: Conf. UCSR0B > donde habilitamos ISR de recepción, habilitamos rx y tx
		UCSR0B = 0;
		
		UCSR0B |= (1<< RXCIE0) |(1<<RXEN0) |(1<<TXEN0);
		
		//Paso 4: Cond. UCSR0C > Asyncrono, Paridad: None, 1 bit de Stop, Data bits 8/bits
		UCSR0C = 0;
		
		UCSR0C |= (1<< UCSZ01)| (1<< UCSZ00);
		
		//Paso #5: Conf. velocidad de Baudrate: 9600
		
		UBRR0 = 103;
		
	}
}

void writeTextUART(char * Texto){
	
	for (int i=0; Texto[i]!='\0'; i++){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = Texto[i];
	}
}

void writeUART(char Caracter){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = Caracter;
}

void recibir(char dato){
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}