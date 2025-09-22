#ifndef ES_LIB_H
#define ES_LIB_H

#include "TM4C129.h" 
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


extern void msDelay(int msec) ;
extern void setSysClk80MHz(void) ;

// serial functions
extern void ES_Serial(int number, char line_format[20]) ;  // eg "9600,5,N,1" is 9600 baud, 5 bit word, no parity, 1 stop bit
extern char ES_getchar(int number) ;
extern void ES_putchar(int number, char c) ;
extern void ES_printf(const char *format, ...) ;

//extern void ES_utob(char *str, uint32_t value, int numbits);
extern char * ES_utob(uint32_t value);

extern void PortN_LEDs(void) ;

extern void enablePortK();
extern void configurePortK();

extern void enablePortC();
extern void configurePortC();


extern void msDelay(int msec) ;

#endif /* ES_LIB_H */