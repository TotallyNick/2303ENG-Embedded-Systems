#ifndef LAB_2_WED_H
#define LAB_2_WED_H

#include "TM4C129.h" 
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


extern void setup_GPIO(void) ;
extern void setup_UART(void) ;

extern void msDelay(int msec) ;
extern void setSysClk80MHz(void) ;

extern void RedirectOutput(void);

extern void banner(char str[]) ;

char read_UART(void) ;
void write_UART(char c);


extern void msDelay(int msec) ;

#endif // LAB_2_WED_H /