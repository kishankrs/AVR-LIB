/*********************************************************************************************************************

----------------------------------------------------------------------------------------------------------------------
                                    16X2 LCD(Liquid Crystal Display) library

 * Description: This Library is for standard 16x2 LCD display, for AVR 16/32 series
             It perform basic text printing to your LCD and capable of operating 
			       in 4 bit/8 bit mode of operation. 

File Name: lcd.h
------------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>


#define cmd_port PORTA  // Command Port- PORTA
#define data_port PORTB // Data Port- PORTB
#define decimal_point 2

#define rs 0
#define rw 2
#define en 1

void lcd_init();  //By default this Library is set in 8-bit mode of operation to change visit to lcd_init function in lcd.c
void lcd_clear();
void lcd_cmd(unsigned char cmd);
void lcd_gotoxy(unsigned char x,unsigned char y);/*x=column(1-16) and y= row(1-2) */
void lcd_Display_char(unsigned char data);
void lcd_Display_String(char *ptr_stringPointer_u8);
void lcd_Display_Integer(int number);
void lcd_Display_Float(float number);
void LCD_itoa(int n, char s[]);
void LCD_ftoa(float n, char *res, int afterpoint);

static void reverse(char s[]);
static void reverseF(char *str, int len);
static int intToStr(int x, char str[], int d);
