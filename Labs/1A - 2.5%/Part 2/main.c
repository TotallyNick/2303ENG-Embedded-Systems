#include "Lab1A.h"
#include <stdint.h>
#define Port_N_DATA (*((uint32_t volatile *)0x400643FC))
#define Mask_Port_N (1<<0)

// ----------------------- P1 ------------------------------


void milliDelay(int count){
	volatile int end = (1000 * count);
	for(int i=0; i < end; i++){
		__NOP();
	}
}

int main(void) {
	
		enablePN() ;
		setPNOutput(Mask_Port_N) ; //PF4=D4, PF1 (Booster Pack 1 - X9 pin 1)
	
	
	// Repeat 5 times with a for loop 
		for(int i = 0; i < 5 ; i++){
			Port_N_DATA |= 0x1 ; 
			milliDelay(1000) ;
			Port_N_DATA &= ~(0x1) ;
			milliDelay(1000) ;
		}
	
	while(1) {

	}

} // end main
	