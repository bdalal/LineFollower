#include<avr/io.h>

void init_uart(){

//UBRRL=103; // 9600
UBRRL=25; // 38400
UBRRH=0;

UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
UCSRB|=(1<<RXEN)|(1<<TXEN);

}

void uart_tx(unsigned char data){

while(!(UCSRA&(1<<UDRE)));
UDR=data;

}

unsigned char uart_rx(){

if(UCSRA&(1<<RXC)){
return UDR;
}
return '0';

}

void uart_txstring(unsigned char *ptr){

while(*ptr!='\0'){
uart_tx(*ptr);
ptr++;
}

}

uart_recvstring(unsigned char* ptr){

*ptr=uart_rx();
while(*ptr!='\r'){
ptr++;
*ptr=uart_rx();
}
*ptr='\0';

}


