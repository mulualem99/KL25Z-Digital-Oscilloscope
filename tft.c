// ======================== tft.c ========================
#include "tft.h"
#include "SPI.h"
#include <stdlib.h>

void TFT_Init(void) {
    // Assume reset/init pins already set high, basic init routine here
    // Send initialization commands to ST7796S (not detailed here)
}

void TFT_DrawPixel(int x, int y, uint16_t color) {
    // Implement based on ST7796S datasheet, set address, write color
}

void TFT_DrawLine(int x0, int y0, int x1, int y1, uint16_t color) {
    // Basic Bresenham algorithm
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        TFT_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void TFT_FillScreen(uint16_t color) {
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 320; x++) {
            TFT_DrawPixel(x, y, color);
        }
    }
}

void TFT_DrawGrid(void) {
    for (int y = 0; y < 480; y += 40) {
        TFT_DrawLine(0, y, 319, y, 0x7BEF);
    }
    for (int x = 0; x < 320; x += 40) {
        TFT_DrawLine(x, 0, x, 479, 0x7BEF);
    }
}