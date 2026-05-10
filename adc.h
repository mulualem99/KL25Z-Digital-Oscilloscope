// ======================== adc.h ========================
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void Init_ADC(void);
uint16_t Read_ADC(void);
float ADC_to_Voltage(uint16_t adc_value);
void Start_ADC_Conversion(uint8_t channel);

#endif // ADC_H