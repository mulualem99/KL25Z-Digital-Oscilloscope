// ======================== main.c ========================
#include "MKL25Z4.h"
#include "adc.h"
#include "Dma.h"
#include "pit.h"
#include "gpio.h"
#include "SPI.h"
#include "tft.h"

#define BUFFER_SIZE 320
#define VREF 3.3f

volatile uint16_t adc_buffer[BUFFER_SIZE];
volatile uint8_t buffer_ready = 0;

void DMA0_IRQHandler(void) {
    DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
    buffer_ready = 1;
}

int main(void) {
    Init_ADC();
    Init_DMA((uint16_t *)adc_buffer, BUFFER_SIZE);
    Init_PIT(48000); // ~1ms
    Init_GPIO();
    Init_SPI();
    TFT_Init();

    TFT_FillScreen(BLACK);
    TFT_DrawGrid();

    while (1) {
        if (buffer_ready) {
            buffer_ready = 0;
            for (int i = 0; i < BUFFER_SIZE - 1; i++) {
                float v1 = adc_buffer[i] * VREF / 65535.0f;
                float v2 = adc_buffer[i+1] * VREF / 65535.0f;
                int y1 = 240 - (int)(v1 * 200);
                int y2 = 240 - (int)(v2 * 200);
                TFT_DrawLine(i, y1, i+1, y2, GREEN);
            }
        }
    }
}