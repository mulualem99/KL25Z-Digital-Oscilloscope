// ======================== adc.c ========================
#include "MKL25Z4.h"
#include "adc.h"

void Init_ADC(void) {
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORTB->PCR[0] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[0] |= PORT_PCR_MUX(0);

    ADC0->SC1[0] = ADC_SC1_ADCH(31); // disable module first
    ADC0->CFG1 = ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0); // 16-bit, Bus clock
    ADC0->SC2 = ADC_SC2_DMAEN_MASK; // enable DMA
}
void Start_ADC_Conversion(uint8_t channel) {
    ADC0->SC1[0] = ADC_SC1_ADCH(channel);
}
