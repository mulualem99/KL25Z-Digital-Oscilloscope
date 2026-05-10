// ======================== pit.c ========================
#include "MKL25Z4.h"
#include "pit.h"
#include "adc.h"
void Init_PIT(uint32_t ldval) {
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR = 0x00; // enable PIT

    PIT->CHANNEL[0].LDVAL = ldval; // e.g. 48000 for 1ms (if bus = 48MHz)
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;

    NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void) {
    if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
        PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
        Start_ADC_Conversion(8); // PTB0 = ADC0_SE8
    }
}