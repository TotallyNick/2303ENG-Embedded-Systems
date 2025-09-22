#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <TM4C129.h>


void configure_PJ(void){
	//GPIOJ pin0 sw2 is pin1
	SYSCTL -> RCGCGPIO |= (1<<8);
	
	while((SYSCTL -> PRGPIO & (1<<8)) == 0){}
	GPIOJ_AHB -> AFSEL &= ~(1<<0);
	GPIOJ_AHB -> PCTL &= ~((0xF<<(0*4)));
	GPIOJ_AHB -> AMSEL &= ~(1<<0);
	GPIOJ_AHB -> DIR &= ~(1<<0);
	GPIOJ_AHB -> DEN |= (1<<0);
	GPIOJ_AHB -> PUR |= (1<<0);
}