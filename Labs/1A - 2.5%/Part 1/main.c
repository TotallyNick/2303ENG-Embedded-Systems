#include "Lab1A.h"

// ----------------------- P1 ------------------------------


void milliDelay(int count){
	volatile int end = (1000 * count);
	for(int i=0; i < end; i++){
		__NOP();
	}
}

int main(void) {
	// Part 1
    enablePF() ;
	setPFOutput((1<<4)|(1<<1)) ; //PF4=D4, PF1 (Booster Pack 1 - X9 pin 1)
	
	
	while(1) {
		writePFData((1<<4)|(1<<1)) ; // pin 0 = 1 (Led), pin 1 = 1 (Booster pin)
		milliDelay(1000) ;
		writePFData(0) ;
		milliDelay(1000) ;
	}
} // end main
	
