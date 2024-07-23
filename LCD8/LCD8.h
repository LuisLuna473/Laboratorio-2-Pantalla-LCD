/*
 * LCD8.h
 *
 * Created: 18/07/2024 13:09:49
 *  Author: luisa
 */ 


#ifndef LCD8_H_
#define LCD8_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

//Función para setear LCD en modo 8Bit
void initLCD8bit(void);

//Función para colocar en el puerto un valor
void LCD_Port(char a); 

//Función para mandar un comando
void LCD_CMD(char a);

//Función para enviar un caracter 
void LCD_Write_CHAR(char c); 

//Función para enviar una cadena
void LCD_Write_String(char *a);

//Desplazamiento hacia la derecha
void Lcd_Shift_Right(void);

//Desplazamiento hacia la izquierda
void Lcd_Shift_Left(void);

//Establecer el cursor 
void LCD_Set_Cursor(char c, char f);

#endif /* LCD8_H_ */