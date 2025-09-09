#include "Lab1A.h"
#include <stdint.h>
#define Port_N_DATA (*((uint32_t volatile *)0x400643FC))
#define Mask_Port_N ((1<<0)|(1<<1))


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
		setPNOutput(Mask_Port_N) ; //PF4=D4, PF1 (Booster Pack 1 - X9 pin 1)
	
		
	
	while(1) {
			
	// STAGE I
		// D1 = ON
			Port_N_DATA |= 0x02 ; 
		// D2 = OFF
			Port_N_DATA &= ~(0x01) ;
		// 1 second delay
			milliDelay(1000) ;
		
	// STAGE II	
		// D1 = OFF
			Port_N_DATA &= ~(0x02) ; 
		// D2 = ON
			Port_N_DATA |= 0x01 ;
		// 1 second delay
			milliDelay(1000) ;
				
	// STAGE III
		// D1 = ON
			Port_N_DATA |= 0x02 ; 
		// D2 = ON
			Port_N_DATA |= 0x01 ;
			// 2 seconds delay
			milliDelay(2000) ;
			
				
	// STAGE IV	
		// D1 = OFF
			Port_N_DATA &= ~(0x02) ; 
		// D2 = OFF
			Port_N_DATA &= ~(0x01) ;
			// 2 seconds delay
			milliDelay(1000) ;


		// STAGE V Return to start
		
	}

} // end main
	