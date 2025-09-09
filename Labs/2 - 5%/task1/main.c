#include "TM4C129.h"
#include "Lab2_wed.h"

// Wednesday
//		Uart		UART3
// 		Baud Rate	38400
//		Comms		7 bits, no parity, 2 stop
//		Prescaler	16

// Instructions:
//		Wire the UART as per Task 0
// 		Compile and run this template to check the connection. It echoes teh keys typed.
//		The different tasks will ask you to rewrite the supplied functions. You can use the same name.


void setup_GPIOA(){
	SYSCTL->RCGCGPIO |= (1<<0); // Init PORT A
	while((SYSCTL->PRGPIO & (1<<0)) == 0); // Wait until Perpherial Ready Register is done
	GPIOA_AHB->AFSEL |= (1<<4)|(1<<5); // Set up port 4 and 5 
	GPIOA_AHB->PCTL &= ~(0x00FF0000); // Clear port control register
	GPIOA_AHB->PCTL |= (0x00110000); // Set port control register
	GPIOA_AHB->DEN |= (1<<4)|(1<<5); // Digital Enable the ports
	GPIOA_AHB->AMSEL &= ~((1<<4)|(1<<5)); // Disable Analog to the ports

}



int main(void) {
	uint8_t c;
	
	setSysClk80MHz() ;   // Do NOT remove. Set the System clock to 80MHz
	
	RedirectOutput(); // Do NOT remove. Redirect output from U3 to the terminal via U4
	
	
	//setup_GPIO() ;  // rewrite function for Part 1
	setup_GPIOA();
	
	setup_UART() ;	// rewrite function for Part 2
		
	banner("Start typing. You should see the keys echoed on the terminal");
	write_UART('G');
	write_UART('O');
	write_UART('\n');
	write_UART('\r');
	
	// ECHO ECHo ECho Echo echo .
	while(1) {
		// echo keys back to you
		// This tests your connection
		c=read_UART();    // read from Uart (rewrite function for Part 3)
		write_UART(c);   // write to Uart (rewrite function for Part 4)
	}
	return 0;
} // end main	


	