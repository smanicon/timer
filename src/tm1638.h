#include <stdint.h>

#ifndef TM1638_H
#define TM1638_H

void TM_init();
void TM_display_digit(uint8_t pos, uint8_t digit);
void TM_display_4_digit(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4); 
void TM_display_off();
void TM_display_on();
uint8_t TM_button_read();
#endif
