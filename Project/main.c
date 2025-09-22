// The project must contain LCD_Display.lib and LCD_Display.h
// This is an example program to draw the demo.

#include <TM4C129.h>
#include <stdint.h>
#include <stdbool.h>

#include "LCD_Display.h"

int main(void) {
	initSPI() ;	// These contain the SPI functions (See LCD_Display.h)
	initLCD() ; // This function turns on and initialises the LCD
	showDemo();

	while(true) {}  // loop forever
}
