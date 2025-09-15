#include <stdlib.h>
#include <stdint.h>

// system clock functions
extern void setSystemClk(uint32_t freq) ;
extern uint32_t getSystemClk(void) ;

// adc functions
extern void Configure_ADC(void) ;
extern uint32_t read_adc_AIN1(void) ;

// uart intitialisation function
extern void Init_UART(void) ;
extern void Initialise_SW1(void)  ;
extern void wait_for_SW1_press(void) ;
extern void U0printf(const char *pcString, ...) ;

