
#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include <stdint.h>
void TM_set_DIO_output();
void TM_set_DIO_input();
void TM_init_port();
void TM_clock_down();
void TM_clock_up();
void TM_STB_down();
void TM_STB_up();
void TM_DIO_down();
void TM_DIO_up();
uint8_t TM_DIO_read();

#endif
