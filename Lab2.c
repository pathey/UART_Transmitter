#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU / (BAUD * 16UL) - 1))

void uart_Init(void){
	
	UBRR0H = (BAUDRATE>>8);	//Set high baud rate register
	UBRR0L = BAUDRATE;		//Set low baud rate register

	UCSR0B = (1 << TXEN0);		//Turn on transmitter by enabling TXEN0

	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);	//set frame format: 8 data bits, 1 stop bit
}

void uart_Transmit(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

int main(void){
	uart_Init();
	
	const char redID[] = "131231396\n";
	
	int i = 0;

	while (1){
		uart_Transmit(redID[i]);
		i += 1;
		if(i == 10){
			_delay_ms(500);
			i = 0;
		}
	}
}
