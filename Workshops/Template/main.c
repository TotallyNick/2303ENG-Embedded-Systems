#include <stdlib.h> 
#include <stdint.h> 
#include <stdbool.h>
#include "TM4C129.h"
#include "ES_Library.h"


int main(void) {
	uint32_t num=0xF; // number to display in different formats
	ES_Serial(0,"19200,8,N,1") ;
	ES_printf("\nHello World\n") ;
	ES_printf("Hex: 0x%X\nBin: 0b%s\nDec: %i\n\n",num,ES_utob(num),num) ;
	while(true) ;
}