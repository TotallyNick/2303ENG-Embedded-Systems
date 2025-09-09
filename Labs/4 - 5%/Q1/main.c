

// Lab 4 Template
// Remember to start and configure TeraTerm

#include <TM4C129.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lib4.h"

volatile int msCount = 0;

void GPION_P0(void){
	SYSCTL -> RCGCGPIO |= (1<<12);
	while ((SYSCTL -> PRGPIO & (1<<12))== 0){}
	GPION -> DIR |= (1<<0); // output
	GPION -> DEN |= (1<<0); // turn digital on
	GPION -> AMSEL &= ~(1<<0); // nomral mode selected
	GPION -> DATA &= ~(1<<0); // clear
}

void SysTick_Init(void){
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 16000 - 1; // 1ms @ 16Hz
	SysTick -> VAL = 0;
	SysTick -> CTRL = (1<<2)|(1<<1)|(1<<0);
}

void SysTick_Handler(void){
	msCount ++;
	if(msCount == 500){
		GPION -> DATA ^= (1<<0); // Toggle
	}
	if(msCount >= 1000){
		msCount = 0; // reset the timer 
	}
}




int main(void)
{
	ES_Serial(0,"115200,8,N,1") ;
	// message to check if the serail connection is working
	ES_printf("\n****************************************\n") ;
	ES_printf("\n Laboratory 4 \n") ;
	ES_printf("\n****************************************\n") ;

	
	GPION_P0();
	SysTick_Init();
	
	while(true) 
		{
		int d=readDec() ;
		ES_printf("\ndec = %i\n",d) ;
		}
	
	return 0;
}
