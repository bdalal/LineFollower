#include<avr/io.h>
#include<util/delay.h>

#define E 2

void enable(){

PORTC|=(1<<E);
_delay_ms(1);
PORTC&=~(1<<E);
_delay_ms(1);

}

void lcd_cmd(unsigned char cmd){

PORTC=0x02|(cmd&0xf0); // transmit higher nibble of commands
enable();
PORTC=0x02|((cmd&0x0f)<<4); // transmit lower nibble of commands
enable();

}

void lcd_data(unsigned char data){

PORTC=0x03|(data&0xf0); // transmit higher nibble of data
enable();
PORTC=0x03|((data&0x0f)<<4); // transmit lower nibble of data
enable();

}

void lcd_init(){

DDRC=0xff; // PORTC in output mode
_delay_ms(15);
lcd_cmd(0x03); // Set LCD output to 4 bit
_delay_ms(45);
lcd_cmd(0x02); // cmd to return home
_delay_ms(15);
lcd_cmd(0x01); // cmd for clear screen
lcd_cmd(0x28); // cmd to operate lcd in 4 bit mode
lcd_cmd(0x0f); // cmd for cursor blinking
lcd_cmd(0x80); // cmd to return cursor to first line

}

void lcd_string(unsigned char *ptr){

while(*ptr!='\0'){
lcd_data(*ptr);
ptr++;
}

}

void gotoxy1(unsigned char pos){

if(pos<16)
lcd_cmd(0x80+pos);
else{
lcd_string("Position 0-15");
_delay_ms(2000);
lcd_cmd(0x01);
}

}

void gotoxy2(unsigned char pos){

if(pos<16)
lcd_cmd(0xc0+pos);
else{
lcd_string("Position 0-15");
_delay_ms(2000);
lcd_cmd(0x01);
}

}

void lcd_showvalue(int n){

lcd_data(n+48);

}

void lcd_num(unsigned int n){

unsigned char buff[30];
sprintf(buff,"%d",n);
lcd_string(buff);

}

void lcd_exit(){

}
