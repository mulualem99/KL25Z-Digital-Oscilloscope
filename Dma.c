// ======================== dma.c ========================
#include "MKL25Z4.h"
#include "Dma.h"

void Init_DMA(uint16_t *buffer, size_t size) {
    SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
    SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

    DMAMUX0->CHCFG[0] = 0;
    DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(40); // ADC0

    DMA0->DMA[0].SAR = (uint32_t)&ADC0->R[0];
    DMA0->DMA[0].DAR = (uint32_t)buffer;
    DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(size * 2);

    DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_ERQ_MASK |
                       DMA_DCR_CS_MASK | DMA_DCR_SSIZE(2) |
                       DMA_DCR_DSIZE(2) | DMA_DCR_DINC_MASK;

    NVIC_EnableIRQ(DMA0_IRQn);
}