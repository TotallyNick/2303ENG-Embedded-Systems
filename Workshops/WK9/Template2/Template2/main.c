#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "adc.h"

extern uint32_t measureAIN1(void) ;	



int main(void) {
	
		setSystemClk(16E6);

    Init_UART();
	
		Configure_ADC() ;
	
		Initialise_SW1() ;
	

    //
    // Display the setup on the console.
    //
    U0printf("\n\nADC ->\n");
    U0printf("  Type: Single Ended\n");
    U0printf("  Samples: One\n");
    U0printf("  Input Pin: AIN1/PE2\n\n");	
	  U0printf("System Clock Frequency : %u\n\n",getSystemClk()) ;
		U0printf("\nPress SW1 to take a measurement of the voltage on pin PE2\n\n") ;
	
	
	while (true) {
	       //abort wait until SW1 button pressed
				wait_for_SW1_press() ;
		
				 uint32_t adc_value = read_adc_AIN1() ;
 
				// Display the AIN1 (PE2) equiavlent digital value on the terminal.
        U0printf("AIN1 = %04d (%03X)\r", adc_value,adc_value);
		
			// wait a bit before detecting the next key press
			for (int i=0; i<160000; i++) __asm("nop") ;

	}
}
