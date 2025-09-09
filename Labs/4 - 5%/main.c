

// Lab 4 Template
// Remember to start and configure TeraTerm

#include <TM4C129.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "Lib4.h"

// ************* main function ***********************
int main(void)
{
	ES_Serial(0,"115200,8,N,1") ;
	
	
	// message to check if the serail connection is working
	ES_printf("\n****************************************\n") ;
	ES_printf("\n Laboratory 4 \n") ;
	ES_printf("\n****************************************\n") ;
	
	// loop forever and enter and print a decimal value.
	// readDec() needed for Part B
	while(true) 
		{
		int d=readDec() ;
		ES_printf("\ndec = %i\n",d) ;
		}
	
	return 0;
}
