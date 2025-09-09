#include "Lab1A.h"
#include <stdint.h>
#define Port_N_DATA (*((uint32_t volatile *)0x400643FC))
#define Mask_Port_N ((1<<0)|(1<<1))
#define LED1 0x02
#define LED2 0x01


// ----------------------- P1 ------------------------------


void milliDelay(int count){
	volatile int end = (1000 * count);
	for(int i=0; i < end; i++){
		__NOP();
	}
}

int main(void) {
	
		// Enable LED 1 and 2
		enablePN() ;
		setPNOutput(Mask_Port_N) ; 
	
		int counter = 0x00;
	
	while(1) {

	// Using a Merge Clear The last two digits in the register
	// 
			Port_N_DATA &= ~(0x03);
			Port_N_DATA |= counter;
			counter++;
			milliDelay(1000);
		
	}

} // end main
