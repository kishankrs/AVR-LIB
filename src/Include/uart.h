#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//define some macros
#define BAUD 9600
#define x (((F_CPU)/(BAUD*16UL))-1)       //define baud

void uart_init (void);
void uart_Tx_char(unsigned char data);
void uart_Tx_string(chaar* StringPtr);
unsigned char uart_recieve(void);
void uart_Tx_number(unit32_t);
void uart iota(unit32_t n, char s[]);
static void reverse(char s[]);