// Lab 4 – Part E (robust + heartbeat)
// TeraTerm: 115200,8,N,1

#include <TM4C129.h>
#include <stdint.h>
#include <stdbool.h>
#include "Lib4.h"

// ===== CONFIG: set this to your real system clock =====
#define SYSTEM_CLOCK_MHZ 16   // set to 80 if you call setSysClk80MHz()

// ===== PWM state =====
static volatile int ticks = 0;        // 0..99 inside each 10 ms PWM frame
static volatile int duty  = 0;        // 0..100 (%), start OFF per spec

// Busy-wait that DOES NOT disable interrupts (safe for SysTick PWM)
static void debounce_delay_ms(uint32_t ms){
    // ~0.5k NOPs per ms per MHz -> tweak factor to taste
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++){
        for (j = 0; j < (SYSTEM_CLOCK_MHZ * 500U); j++){ __NOP(); }
    }
}

// LEDs: PN0 (D2), PN1 (D1), PF0 (D4), PF4 (D3)
static void LEDs_Init(void){
    // --- Port N (PN0, PN1) ---
    SYSCTL->RCGCGPIO |= (1U << 12);
    while ((SYSCTL->PRGPIO & (1U << 12)) == 0) {}
    GPION->AFSEL &= ~((1U<<0)|(1U<<1));
    GPION->PCTL  &= ~((0xF<<(0*4)) | (0xF<<(1*4)));
    GPION->AMSEL &= ~((1U<<0)|(1U<<1));
    GPION->DIR   |=  (1U<<0)|(1U<<1);
    GPION->DEN   |=  (1U<<0)|(1U<<1);
    GPION->DATA  &= ~((1U<<0)|(1U<<1));

    // --- Port F AHB (PF0, PF4) ---
    SYSCTL->RCGCGPIO |= (1U << 5);
    while ((SYSCTL->PRGPIO & (1U << 5)) == 0) {}

    GPIOF_AHB->AFSEL &= ~((1U<<0)|(1U<<4));
    GPIOF_AHB->PCTL  &= ~((0xF<<(0*4)) | (0xF<<(4*4)));
    GPIOF_AHB->AMSEL &= ~((1U<<0)|(1U<<4));
    GPIOF_AHB->DIR   |=  (1U<<0)|(1U<<4);
    GPIOF_AHB->DEN   |=  (1U<<0)|(1U<<4);
    GPIOF_AHB->DATA  &= ~((1U<<0)|(1U<<4));
}

static void Switches_Init(void){
    // PJ0 (SW1), PJ1 (SW2) inputs with pull-ups (active-LOW)
    SYSCTL->RCGCGPIO |= (1U << 8);
    while ((SYSCTL->PRGPIO & (1U << 8)) == 0) {}
    GPIOJ_AHB->AFSEL &= ~((1U<<0)|(1U<<1));
    GPIOJ_AHB->PCTL  &= ~((0xF<<(0*4)) | (0xF<<(1*4)));
    GPIOJ_AHB->AMSEL &= ~((1U<<0)|(1U<<1));
    GPIOJ_AHB->DIR   &= ~((1U<<0)|(1U<<1));
    GPIOJ_AHB->DEN   |=  ((1U<<0)|(1U<<1));
    GPIOJ_AHB->PUR   |=  ((1U<<0)|(1U<<1));
}

static inline void LEDS_ON(void){
    GPION->DATA     |= (1U<<0)|(1U<<1);
    GPIOF_AHB->DATA |= (1U<<0)|(1U<<4);
}
static inline void LEDS_OFF(void){
    GPION->DATA     &= ~((1U<<0)|(1U<<1));
    GPIOF_AHB->DATA &= ~((1U<<0)|(1U<<4));
}

static void SysTick_Init_10kHz(void){
    SysTick->CTRL = 0;
    uint32_t reload = (SYSTEM_CLOCK_MHZ * 1000000U) / 10000U; // Fclk/10k
    SysTick->LOAD = reload - 1;   // 1600-1 for 16 MHz, 8000-1 for 80 MHz
    SysTick->VAL  = 0;
    SysTick->CTRL = (1U<<2)|(1U<<1)|(1U<<0); // CLKSRC|TICKINT|ENABLE
}

static void setDutyClampedPrint(int pct){
    if (pct < 0)   pct = 0;
    if (pct > 100) pct = 100;
    duty = pct;
    ES_printf("%d%%\r\n", pct);
}


void SysTick_Handler(void){
    int d = duty;
    if (d < 0)   d = 0;
    if (d > 100) d = 100;

    if (ticks < d) LEDS_ON(); else LEDS_OFF();
		ticks++;
    if (ticks >= 100) ticks = 0;   // reset every 100 ticks = 10 ms frame
	
}

int main(void){
    ES_Serial(0, "115200,8,N,1");
    ES_printf("\r\n*** Lab 4 Part E (robust) ***\r\n");
    ES_printf("SysClk=%d MHz, PWM=100 Hz, SysTick=10 kHz\r\n", SYSTEM_CLOCK_MHZ);

    LEDs_Init();
    Switches_Init();
    SysTick_Init_10kHz();

    setDutyClampedPrint(0);   // start OFF

    while (true){
        // SW1 (PJ0) increase
        if ((GPIOJ_AHB->DATA & (1U<<0)) == 0){
            setDutyClampedPrint(duty + 10);
            debounce_delay_ms(150);
        }
        // SW2 (PJ1) decrease
        if ((GPIOJ_AHB->DATA & (1U<<1)) == 0){
            setDutyClampedPrint(duty - 10);
            debounce_delay_ms(150);
        }
    }
}
