// ======================== tft.h ========================
#ifndef _TFT_H_
#define _TFT_H_

#include <stdint.h>

#define BLACK   0x0000
#define GREEN   0x07E0
#define WHITE   0xFFFF

void TFT_Init(void);
void TFT_DrawPixel(int x, int y, uint16_t color);
void TFT_DrawLine(int x0, int y0, int x1, int y1, uint16_t color);
void TFT_FillScreen(uint16_t color);
void TFT_DrawGrid(void);

#endif