#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <TM4C129.h>
#include "ES_Lib.h"			// Useful file functions
#include "workshop7.h" // my own header

int main(void) {
	
	configure_D1() ;
	configure_PJ();
	
	while (true) {
	
	/*	-- question 3 code 
	msDelay(500);
	flag = D1_toggle(flag);
	*/
		
  // SW1 (PJ0) increase
  if ((GPIOJ_AHB->DATA & (1U<<0)) == 0){
		flag = D1_toggle(flag);
		//debounce
		msDelay(150);
  }

	
	
	}
}
