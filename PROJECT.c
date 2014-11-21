/*

Black Line Follower with Obstace Detection and Avoidance with Wireless Speed Control

*/

#include "cc2500.h"
#include "lcd.h"
#include "motor.h"
#include "timer_init.h"

// ADD RESPECTIVE MACRO DEFINITIONS HERE
#define IRL1 (!(PINA&(1<<1))) // Check Digital Line Sensor 1 for PRESENCE of line
#define IRL3 (!(PINA&(1<<3))) // Check Digital Line Sensor 3 for PRESENCE of line
#define IRL5 (!(PINA&(1<<5))) // Check Digital Line Sensor 5 for PRESENCE of line
#define TSOP (!(PINA&(1<<6))) // Check TSOP sensor for PRESENCE of obstacle
#define DIRL1 DDRA&=~(1<<1) // SET INPUT
#define DIRL3 DDRA&=~(1<<3) // SET INPUT
#define DIRL5 DDRA&=~(1<<5) // SET INPUT
#define DTSOP DDRA&=~(1<<6) // SET INPUT


void lineFollow(); // Line follower logic
void obs(); // Obstacle detector/avoider logic
void rpmControl(); // Wireless rpm control logic
void rpmDisplay(); // rpm display on LCD logic

void main(){

	init_motor();
	init_uart();
	init_cc2500();
	lcd_init();
	init_timer0_normal();

/*
WRITE PORT INITIALIZATION CODE HERE
*/
	DIRL1;
	DIRL3;
	DIRL5;
	DTSOP;
	
	lcd_num(75);
	lineFollow();

}

void lineFollow(){

	unsigned int flag=1; // To decide whether to turn right or left when all 3 sensors go off line
	unsigned char temp;
	unsigned int rpm=75;
	
	while(1){
		temp=uart_rx();
uart_tx(temp);
		if((!IRL1 && IRL3 && !IRL5) || (IRL1 && IRL3 && IRL5)){ // Go straight if only 1 line found or if a junction is encountered
			forward();
		}
		if((!IRL1 && IRL3 && IRL5) || (!IRL1 && !IRL3 && IRL5)){ // Turn right if line curves or turns sharply to right until LED3 detects line again		
			while(!IRL3){
			r360();}
		}
		if((IRL1 && IRL3 && !IRL5) || (IRL1 && !IRL3 && !IRL5)){ //Turn left if line curves or turns sharply to left until LED3 detects line again
			while(!IRL3){
			l360();}
		}
		if(IRL1 && !IRL3 && IRL5){ //Turn right until LED3 detects line again, if LED1 and LED5 detect line but LED3 doesn't
			r360();
		}
		if(!IRL1 && !IRL3 && !IRL5){ // Turn left until line detected if all 3 sensors go off the line and flag=1
			l360();
		}
		if(TSOP){ // Call obs() function if obstacle detected
			obs();
		}
		if(temp=='w'){
			if(rpm<=15 && rpm>=3){
				rpm*=5;
			}
			gotoxy1(0);
			lcd_num(rpm);
		}		
		if(temp=='s'){
			if(rpm>=15 && rpm<=75){
				rpm/=5;
			}
			gotoxy1(0);
			lcd_num(rpm);
		}
		if(rpm==15){
						delay_200ms();
			stop();
			delay_200ms();
		}
		if(rpm==3){
delay_1s();
			stop();
			delay_1s();
		}
	}
}

void obs(){

	while(1){

		if(TSOP){ // Turn to the right and follow the obstacle if detected
			right();
		}
		if(!TSOP){
			left();
		}
		if(IRL1 || IRL3 || IRL5){ // Call lineFollow() if line detected again
			lineFollow();
		}

	}
}
