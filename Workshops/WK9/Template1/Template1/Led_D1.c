#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <TM4C129.h>

// Question 1
void configure_D1(void){
	//GPION pin1
	SYSCTL -> RCGCGPIO |= (1<<12);
	
	while((SYSCTL -> PRGPIO & (1<<12)) == 0){}
	GPION -> DIR |= (1<<1); // output
	GPION -> DEN |= (1<<1); // turn digital on
	GPION -> AMSEL &= ~(1<<1); // nomral mode selected
	GPION -> DATA &= ~(1<<1); // clear

}

 void msDelay(int ms){
	ms = ms * 2000;
	 for(int i=0;i<ms; i++){__NOP();}
 }

 
 
 // Question 2
 void D1_on(void){
 GPION -> DATA |= (1<<1); // Set
 }
	 
 void D1_off(void){
 GPION -> DATA &= ~(1<<1); // Clear
 }
 
 
 // Question 3 
 int D1_toggle(int flag){
	 
	if(flag == 1){
 	GPION -> DATA ^= (1<<1); // Toggle
	return(0); // reset the flag
		  
	} else {
 	GPION -> DATA ^= (1<<1); // Toggle
	return(1); // put the flag high for next round
	} 
}