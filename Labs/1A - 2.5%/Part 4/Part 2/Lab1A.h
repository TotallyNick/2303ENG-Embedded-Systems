#ifndef LAB1A_H
#define LAB1A_H

#include "TM4C129.h" 
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

extern char serialRead(void) ;
extern void serialWrite(char c) ;
extern void enableSerial(void) ;
extern void setBaudRate115200(void) ;

extern void enablePF(void) ;
extern void setPFOutput(uint8_t pins) ;
extern void setPFInput(uint8_t pins)  ;
extern void writePFData(uint8_t value) ;
extern uint8_t readPFData(void) ;

extern void enablePJ(void) ;
extern void setPJOutput(uint8_t pins) ;
extern void setPJInput(uint8_t pins)  ;
extern void writePJData(uint8_t value) ;
extern uint8_t readPJData(void) ;

extern void enablePN(void) ;
extern void setPNOutput(uint8_t pins) ;
extern void setPNInput(uint8_t pins)  ;
extern void writePNData(uint8_t value) ;
extern uint8_t readPNData(void) ;

extern void msDelay(int msec) ;

#endif /* LAB1A_H */