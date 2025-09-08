#include <stdlib.h> 
#include <TM4C129.h>


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
	
	// 16 Mhz * 0.5s = 8,000,000 ticks (no prescale)
	
	// Disable timer while configuring
	TIMER1 -> CTL &= ~(1<<0);
	
	// 32-bit mode
	TIMER1 -> CFG = 0x0;
	
	// One-shot-mode
	TIMER1 -> TAMR = 0x1;
	
	// prescaler = 0
	TIMER1 -> TAPR = 256;
	
	// interval
	TIMER1 -> TAILR = 31250;
	
}

void delay_500ms_oneshot(void){
	// clear  any prior timeout and start one-shot
	TIMER1 -> ICR |= (1<<0);
	TIMER1 -> CTL |= (1<<0);
	
	// Poll for timeout
	while((TIMER1 -> RIS & (1<<0)) == 0); // wait
	
	//ack timeout
	TIMER1 -> ICR = (1<<0);
}

int main(void) {
	gpio_pk();
	timer_1A_init();
	
	
	// Produce a 1 Hz square wave on pk2 using successive 0.5s
	while(1){
		GPIOK -> DATA ^= (1u<<2); // toggle
		delay_500ms_oneshot();
	}

}