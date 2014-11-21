#include "uart.h"
#include<avr/io.h>
#include<util/delay.h>

void init_cc2500(){

DDRC|=(1<<3);
_delay_ms(5000);

uart_tx('a'); // Self Address
_delay_ms(100);
uart_tx('b'); // Remote Address
_delay_ms(100);
uart_tx('!'); // Channel
_delay_ms(100);

PORTC|=(1<<3);
_delay_ms(500);
PORTC&=~(1<<3);

}
