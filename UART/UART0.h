/*
 * UART0.h
 *
 * Created: 18/07/2024 13:13:31
 *  Author: luisa
 */ 


#ifndef UART0_H_
#define UART0_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include <stddef.h>

/*
	DEFINICIONES DE VARIABLES
*/
#define M9600 1


//Modo 9600
void SetupUART0(uint8_t MODO);
void writeTextUART(char * Texto);
void writeUART(char Caracter);
void procesarCadena(char *cadena_mc);
void recibir(char dato); 


#endif /* UART0_H_ */