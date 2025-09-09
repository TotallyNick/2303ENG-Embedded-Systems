// Lab 4 Template
// Remember to start and configure TeraTerm


// Q2
#include <TM4C129.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lib4.h"

volatile int msCount = 0;
volatile int dutyMs = 500;

void GPION_P0(void){
	SYSCTL -> RCGCGPIO |= (1<<12);
	while ((SYSCTL -> PRGPIO & (1<<12))== 0){}
	GPION -> DIR |= (1<<0); // output
	GPION -> DEN |= (1<<0); // turn digital on
	GPION -> AMSEL &= ~(1<<0); // nomral mode selected
	GPION -> DATA &= ~(1<<0); // clear
}

void SysTick_Init(void){
	SysTick -> CTRL = 0; // Disable while configuring
	SysTick -> LOAD = 16000 - 1; // 1ms @ 16Hz
	SysTick -> VAL = 0; // Clear current 
	SysTick -> CTRL = (1<<2)|(1<<1)|(1<<0); // CLKSRC = core | TICKINT | ENABLE
}

void Set_DutyCycle(int percent){
	// setting bounds
	if (percent < 0){ percent = 0; }
	if (percent > 100){ percent = 100;} 
	dutyMs = (1000 * percent) / 100; 
}




void SysTick_Handler(void){
	msCount ++;
	if(msCount >= 1000){
		msCount = 0; // reset the timer 
	}
	
	if(dutyMs <= 0){
		GPION -> DATA &= ~(1<<0);
	} else if (dutyMs >= 1000) {
		GPION -> DATA |= (1<<0);
	}else{
		if(msCount<dutyMs) GPION -> DATA |= (1<<0); // On
		else GPION -> DATA &= ~(1<<0); //off
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
	
	Set_DutyCycle(50);
	ES_printf("PART A: PN0 Blinking at 50% duty. \r\n");
	
	ES_printf("PART B: Enter a duty cycle (0..100) and press enter. \r\n");
	
	while(true) 
		{
		int percent = readDec() ;
			
		Set_DutyCycle(percent);
		ES_printf("Duty set to %d%% (ON = %d ms of 1000 ms)\r\n",percent,dutyMs) ;
		}
	
	return 0;
}
