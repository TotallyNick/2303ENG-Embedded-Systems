// Lab 4 Template
// Remember to start and configure TeraTerm


// Q4
#include <TM4C129.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lib4.h"

volatile int ticks = 0;
volatile int duty = 500;

void GPION_F_PINS(void){
	
	// Port  N
	SYSCTL -> RCGCGPIO |= (1<<12);
	while ((SYSCTL -> PRGPIO & (1<<12))== 0){}
	GPION -> DIR |= (1<<0)|(1<<1); // output
	GPION -> DEN |= (1<<0)|(1<<1); // turn digital on
	GPION -> AMSEL &= ~((1<<0)|(1<<1)); // nomral mode selected
	GPION -> DATA &= ~((1<<0)|(1<<1)); // clear
		
	// Port F
	SYSCTL -> RCGCGPIO |= (1<<5);
	while ((SYSCTL -> PRGPIO & (1<<5))== 0){}
	GPIOF_AHB -> DIR |= (1<<0)|(1<<4); // output
	GPIOF_AHB -> DEN |= (1<<0)|(1<<4); // turn digital on
	GPIOF_AHB -> AMSEL &= ~((1<<0)|(1<<4)); // nomral mode selected
	GPIOF_AHB -> DATA &= ~((1<<0)|(1<<4)); // clear
}

void SysTick_Init(void){
	SysTick -> CTRL = 0; // Disable while configuring
	SysTick -> LOAD = 16000 - 1; // 1ms @ 16Hz
	SysTick -> VAL = 0; // Clear current 
	SysTick -> CTRL = (1<<2)|(1<<1)|(1<<0); // CLKSRC = core | TICKINT | ENABLE
}
 void delayMs(int ms){
	// 
	ms = ms * 8000;
	 for(int i=0;i<ms; i++){__NOP();}
 }

void LEDS_ON(void){
	GPIOF_AHB -> DATA |= (1<<0) | (1<<4);
	GPION -> DATA |= (1<<0) | (1<<1);
}

void LEDS_OFF(void){
	GPIOF_AHB -> DATA &= ~((1<<0) | (1<<4));
	GPION -> DATA &= ~((1<<0) | (1<<1));
}

void SysTick_Handler(void){
	if (ticks < duty){ 
		LEDS_ON();
	}else{
		LEDS_OFF();
	}
	
	ticks ++;
	if(ticks >= 100){
		ticks = 0; // next frame of the PWM
	}
	
}

int main(void)
{
	ES_Serial(0,"115200,8,N,1") ;
	// message to check if the serail connection is working
	ES_printf("\n****************************************\n") ;
	ES_printf("\n Laboratory 4 \n") ;
	ES_printf("\n****************************************\n") ;

	
	GPION_F_PINS();
	SysTick_Init();
	
	ES_printf("PART D: All LEDS sweep together \r\n");
	
	while(true) 
		{
       for (uint32_t d = 0; d <= 100; d++){ 
				duty = d; 
				delayMs(50); 
			 }
       for (int d = 100; d >= 0; d--){ 
				duty = (uint32_t)d; 
				delayMs(50); 
			 }
		}
	
	return 0;
}
