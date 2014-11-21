#include<avr/io.h>

#define TOVOF !(TIFR&(1<<TOV0))

void init_timer0_normal(){ // Timer for 1 second

TCCR0=(1<<CS00)|(1<<CS02);
TCNT0=99;

}

void delay_1s(){

int i;
for(i=0;i<99;i++){
while(TOVOF); // Wait till TOV0 becomes 1
TIFR|=(1<<TOV0); // Clear flag
TCNT0=99;
}

}

void delay_200ms(){

int i;
for(i=0;i<18;i++){
while(TOVOF); // Wait till TOV0 becomes 1
TIFR|=(1<<TOV0); // Clear flag
TCNT0=18;
}

}
