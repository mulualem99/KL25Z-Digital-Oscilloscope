// ======================== gpio.c ========================
#include "MKL25Z4.h"
#include "gpio.h"

void Init_GPIO(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    PORTA->PCR[1] = PORT_PCR_MUX(1);
    PTA->PDDR &= ~(1 << 1); // input
}