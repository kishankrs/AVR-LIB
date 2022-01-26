#include "uart.h"
#include<string.h>


// Function to Initialize UART
void uart_init (void)
{
	UBRRH = (x>>8); //shift the register right by 8 bits(putting x value in UBRRH id its higher than 8 bit)
	UBRRL = x;      //set baud rate
	
	UCSRB|= (1<<TXEN) | (1<<RXEN) ; //Enable receiver and transmitter
	
	//	UCSRC |= (1<<URSEL) | (1<<USBS) | (3<<UCSZ0); //8bit data, 2 stop bits [uncomment this line & comment next line if you wish to send 2 stop bits]
		UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1); //8bit data, 1 stop bit
		
}

// Function to send data 
void uart_Tx_char (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));   // wait while register is free
	UDR = data;						//  load data in the register
	
}

//Function to receive data
unsigned char uart_receive(void)
{
	while(!(UCSRA) & (1<<RXC)); // wait while data is being received
	return UDR;				   // return 8-bit data 
	
}

void uart_Tx_string(char* StringPtr){
	
	while(*StringPtr !=0x00){
		uart_Tx_char(*StringPtr);
	StringPtr++;}

}

void uart_itoa(uint32_t n, char s[])
{
	int i, sign;
	
	if((sign = n) < 0) //record sign
	n = -n; //make n positive
	i = 0;
	do{                //generaate digits in reverse order
		 s[i++] = n % 10 + '0'; //get next digit
	}
	
	while ((n /= 10) > 0); //delete it
	if (sign < 0)
	s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	
}

static void reverse(char s[])
{
	int i,j;
	char c;
	
	for (i = 0,j = strlen(s)-1; i<j; i++, j--)
		
		{
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
}

void uart_Tx_number(uint32_t tmp)
{
	char s[5];
	uart_itoa(tmp,s);
	uart_Tx_string(s);
	
}
