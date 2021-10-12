/*
 * LCD_Display_Ex.c
 *
 * Created: 12-10-2021 08:23:07 PM
 * Author : Kishankrs
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"


int main(void)
{
	DDRA=0xff;           //making lcd command port as output
	DDRB=0xff;           //making lcd data port as output
	lcd_init();
	lcd_Display_String("Hi,");
	lcd_gotoxy(5,1);
	lcd_Display_String("LCD API: AVR");
	lcd_gotoxy(1,2);
	lcd_Display_String("BY KISHAN");
	return 0;
	
}


