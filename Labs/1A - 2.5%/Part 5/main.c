#include "Lab1A.h"
#include <stdint.h>
#define Port_N_DATA (*((uint32_t volatile *)0x400643FC))
#define Port_J_DATA (*((uint32_t volatile *)0x400603FC))
#define Mask_Port_N ((1<<0)|(1<<1))
#define Mask_Port_J (1<<0)
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
		setPNOutput(Mask_Port_N) ; //PF4=D4, PF1 (Booster Pack 1 - X9 pin 1)
		// Enable Port J for Switch 1
		enablePJ();
		setPJInput(Mask_Port_J);
		
		int pressed = 0;
	
	
	while(1) {
		// Start by reading the data of the switch
			int flag = readPJData();
		
			if(flag != 0){
				switch(pressed){
			// STAGE I - 00
					case 1:
				// D1 = OFF
				Port_N_DATA &= ~(LED1) ; 
				// D2 = OFF
				Port_N_DATA &= ~(LED2) ;
					// Iterate and EXIT
						pressed++;
						break;
					
			// STAGE II	- 01
					case 2:
				// D1 = ON
					Port_N_DATA |= LED1 ; 
				// D2 = OFF NO CHANGE
						//Iterate and EXIT
						pressed++;
						break;
					
			// STAGE III - 10
					case 3:
				// D1 = OFF
					Port_N_DATA &= ~(LED1) ; 
				// D2 = ON
					Port_N_DATA |= LED2 ;
					//Iterate and EXIT
						pressed++;
						break;
					
			// STAGE IV	- 11
					case 4:
				// D1 = ON
					Port_N_DATA |= (LED1) ; 
				// D2 = ON - NO CHANGE
					//Reset and EXIT
						pressed = 0;
						break;
				}
				
				// delay between presses
				milliDelay(1000);
			}
			
	} // end main
	

}
