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

void setup_UART3(){
	SYSCTL->RCGCUART |= (1<<3); // Enable UART3
	while((SYSCTL->PRUART & (1<<3)) == 0); // Wait until Perpherial is Ready
	UART3->CTL &= ~(0x0); // stop control
	UART3->IBRD = 130; // Set integer board to 130
	UART3->FBRD = 14; // Set fractional board to 14
	UART3->LCRH = 0x48; // Set line control to calculated number in Prelim
	UART3->CC = 0; // Use System Clock
	UART3->CTL = 0x301; // Set control to calculated number is prelim 

}

char read_UART3(){

		char c; 
	
		while(UART3->FR & (1<<4)); // wait until bit 4 of the UART FLAG is on that means the FIFO register is Full 
	
		c  = (UART3->DR & 0xFF); // Write the contents of c into the data register 

		return(c);
}

void write_UART3(char c){

		while(UART3->FR & (1<<5)); // wait until bit 5 of the UART FLAG is on that means the FIFO register is Empty 
		UART3->DR = c; // Write the Data out to the DATA Register

}


uint32_t Read_Num(){
	
	
	uint32_t total = 0; // total of all of the characters
	char c; // current character
	

	while (1){
		
		// read inputs
		c =read_UART3();   
		write_UART3(c);   
		
		// if the key pressed was enter
		if(c == '\r'){break;}// Break out of the loop
		
		// if the numbers entered are in range of 0-9
		if(c >= '0' && c <= '9'){
			
				// push the total up a factor of 10 and then add the current character to the end
				// also convert to a integer from character
				total = total * 10 + (c - '0') ;
		}
	}
	
		
	// Go Past inputs
	write_UART('\n');
	write_UART('\r');
	
	// after enter is entered return the number 
	return(total);
}

void Write_Num(uint32_t num){
	
	
	char digits[10]; // To Hold Each Digit before printing
	int i = 0; // counter
	
	while(num > 0){
	
		// add chars to the arrary
		digits[i++] =(num%10) + '0'; // convert the number into a character to print
		num = num / 10; // remove the last character out of the num sequence
	}
	
	while(i > 0){
		write_UART3(digits[--i]); // print it out
	}
	
}


int main(void) {
	uint8_t c;
	
	setSysClk80MHz() ;   // Do NOT remove. Set the System clock to 80MHz
	
	RedirectOutput(); // Do NOT remove. Redirect output from U3 to the terminal via U4
	
	// My Function
	setup_GPIOA();
	
	
	// My Function
	setup_UART3();
		
	banner("Start typing. You should see the keys echoed on the terminal");
	write_UART('G');
	write_UART('O');
	write_UART('\n');
	write_UART('\r');
	
	
	// ECHO ECHo ECho Echo echo .
	while(1) {

		int num = Read_Num();    // My Function
		Write_Num(num);		// My Function
		
		
		write_UART3('\r'); // So it doesnt over write itself 
		write_UART3('\n');
		
	}
	return 0;
} // end main	


	