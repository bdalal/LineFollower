#include<avr/io.h>
#include<util/delay.h>

void init_motor(){

DDRD|=((1<<4)|(1<<5)|(1<<6)|(1<<7));

}

//4,5 - Left
//6,7 - Right

void forward(){

PORTD|=(1<<4)|(1<<6);
PORTD&=~((1<<5)|(1<<7));

}

void reverse(){

PORTD|=(1<<5)|(1<<7);
PORTD&=~((1<<4)|(1<<6));

}

void left(){

PORTD&=~((1<<4)|(1<<5));
PORTD|=(1<<6);
PORTD&=~(1<<7);

}

void right(){

PORTD&=~((1<<6)|(1<<7));
PORTD|=(1<<4);
PORTD&=~(1<<5);

}

void stop(){

PORTD&=~((1<<4)|(1<<5)|(1<<6)|(1<<7));

}

void r360(){

PORTD&=~(1<<6);
PORTD|=(1<<7);
PORTD|=(1<<4);
PORTD&=~(1<<5);

}

void l360(){

PORTD|=(1<<6);
PORTD&=~(1<<7);
PORTD&=~(1<<4);
PORTD|=(1<<5);

}