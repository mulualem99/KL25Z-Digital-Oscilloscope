// ======================== spi.c ========================
#include "MKL25Z4.h"
#include "SPI.h"

void Init_SPI(void) {
    SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    PORTD->PCR[0] = PORT_PCR_MUX(2); // SPI0_PCS0
    PORTD->PCR[1] = PORT_PCR_MUX(2); // SPI0_SCK
    PORTD->PCR[2] = PORT_PCR_MUX(2); // MOSI

    SPI0->C1 = SPI_C1_MSTR_MASK | SPI_C1_SPE_MASK;
    SPI0->BR = SPI_BR_SPPR(2) | SPI_BR_SPR(8); // adjust speed
}

void SPI_Write(uint8_t d) {
    while (!(SPI0->S & SPI_S_SPTEF_MASK)) {}
    SPI0->D = d;
    while (!(SPI0->S & SPI_S_SPRF_MASK)) {}
    (void)SPI0->D;
}