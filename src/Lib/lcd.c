/*********************************************************************************************************************
----------------------------------------------------------------------------------------------------------------------
                                    16X2 LCD(Liquid Crystal Display) library


 * Description: This Library is for standard 16x2 LCD display, for AVR 32 series
             It perform basic text printing to your LCD and capable of operating 
			       in 4 bit/8 bit mode of operation. 

File Name: lcd.c

------------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/


#include "lcd.h"
#include <string.h>


void lcd_init()
{
	cmd_port &= ~(1<<en);  //set en pin 0
	_delay_ms(2);

	lcd_cmd(0x38);   // set in 8 Bit mode
	_delay_ms(10);

	lcd_cmd(0X0F);   //display On cursor Blink
	_delay_ms(10);

	lcd_cmd(0x01);  //clear screen
	_delay_ms(10);


	lcd_cmd(0x80); //return Home
	_delay_ms(10);
}

void lcd_clear()
{
	unsigned char x=0x01;
	lcd_cmd(x);
	
}
void lcd_cmd(unsigned char cmd)
{
	cmd_port &= ~(1<<rs); //set rs =0 command register selected
	_delay_ms(2);

	cmd_port &= ~(1<<rw); //set rw = 0 in write mode
	_delay_ms(2);

	data_port = cmd;     //send command on data pins
	_delay_ms(2);

	cmd_port |= (1<<en);  // 1-  High to low pulse on E pin latch data to RAM of LCD
	_delay_ms(2);

	cmd_port &= ~(1<<en);  //0
	_delay_ms(2);
	

}

void lcd_Display_char(unsigned char data)
{
	
	cmd_port |= (1<<rs); //set rs =1 data register selected
	_delay_ms(2);

	cmd_port &= ~(1<<rw); //set rw = 0 in write mode
	_delay_ms(2);

	data_port = data;     //send data on data pins
	_delay_ms(2);

	cmd_port |= (1<<en);  // 1-  High to low pulse on E pin latch data to RAM of LCD
	_delay_ms(2);

	cmd_port &= ~(1<<en);  //0
	_delay_ms(2);

}
void lcd_Display_String(char *ptr_stringPointer_u8)
{
	while((*ptr_stringPointer_u8)!=0)
	lcd_Display_char(*ptr_stringPointer_u8++); // Loop through the string and display char by char
}

void lcd_gotoxy(unsigned char x,unsigned char y)
{
	unsigned char a[]={0x80,0xC0,0x90,0xC4};
	lcd_cmd(a[y-1]+x-1);
	_delay_us(100);
}
void LCD_itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
	n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
		} while ((n /= 10) > 0);     /* delete it */
		if (sign < 0)
		s[i++] = '-';
		s[i] = '\0';
		reverse(s);
	}
	
void LCD_ftoa(float n, char *res, int afterpoint)
	{
		// Extract integer part
		int ipart = (int)n;

		// Extract floating part
		float fpart = n - (float)ipart;

		// convert integer part to string
		int i = intToStr(ipart, res, 1);

		// check for display option after point
		if (afterpoint != 0)
		{
			res[i] = '.';  // add dot

			// Get the value of fraction part upto given no.
			// of points after dot. The third parameter is needed
			// to handle cases like 233.007
			fpart = fpart * pow(10, afterpoint);

			intToStr((int)fpart, res + i + 1, afterpoint);
		}
	}
static void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

static void reverseF(char *str, int len)
{
	int i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}
static int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';

	reverseF(str, i);
	str[i] = '\0';
	return i;
}

void lcd_Display_Integer(int number)
{
	char s[5];
	LCD_itoa(number,s);
	lcd_Display_String(s);
	
}
void lcd_Display_Float(float number)
{
	char res[10];
	LCD_ftoa(number,res,decimal_point);
	lcd_Display_String(res);
}