#include <stdlib.h> 
#include <TM4C129.h>


void Timer1A_Handler(void){
	GPIOK -> DATA ^= (1<<2); // Toggle
	TIMER1 -> ICR = (1<<0); // Clear timeout
}

void gpio_pk(void){
	SYSCTL -> RCGCGPIO |= (1<<9); // turn on port k
	while((SYSCTL->PRGPIO & (1<<9)) == 0); // wait until port K is ready
	
	// PK2 as digital output
	GPIOK -> DIR |= (1<<2);
	GPIOK -> DEN |= (1<<2);

}


void timer_1A_init(void){
	SYSCTL ->RCGCTIMER |= (1<<1); // turn on timer 1
	while((SYSCTL->PRTIMER & (1<<1)) == 0); // wait until timer is on
	
	// 16 Mhz * 0.5s = 8,000,000 ticks (no prescale) p997 I think ill need to go over this 
	
	// Disable timer while configuring
	TIMER1 -> CTL &= ~(1<<0);
	
	// 32-bit mode
	TIMER1 -> CFG = 0x0;
	
	// Periodic Mode
	TIMER1 -> TAMR = 0x2;

	// prescaler = 0
	TIMER1 -> TAPR = 0;
	
	// interval
	TIMER1 -> TAILR = 8000000;
	
	// Clear Prior Timeout
	TIMER1 -> ICR = (0<<0);
	
	// Enable Timeout
	TIMER1 -> IMR = (1<<0);
	
	// NVIC TIMER1A is interrupt number 37
	NVIC -> IPR[37] = (3<<5); // Priority set 3
	NVIC -> ISER[1] = (1<<5); // Enable IRQ
	
	// Enable Timer 1A
	TIMER1 -> CTL |= (1<<0); 
}

int main(void) {
	__disable_irq();
	gpio_pk();
	timer_1A_init();
	__enable_irq();
	
	// Produce a 1 Hz square wave on pk2 using successive 0.5s
	while(1){
		__WFI();
	}

}