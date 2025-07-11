#include <avr/io.h>
#include <stdint.h>
#include "motherboard.h"

#define TM_STB PD2
#define TM_CLK PD3
#define TM_DIO PD4

#define TM_PORT PORTD
#define TM_PIN PIND
#define TM_DDR DDRD

void TM_init_port() {
  TM_DDR |= (1 << TM_STB) | (1 << TM_CLK) | (1 << TM_DIO);
  TM_PORT |= (1 << TM_STB) | (1 << TM_CLK) | (1 << TM_DIO);
}

void TM_set_DIO_output() { TM_DDR |= (1 << TM_DIO); }

void TM_set_DIO_input() { TM_DDR &= ~(1 << TM_DIO); }

void TM_clock_down() { TM_PORT &= ~(1 << TM_CLK); }

void TM_clock_up() { TM_PORT |= (1 << TM_CLK); }

void TM_STB_down() { TM_PORT &= ~(1 << TM_STB); }

void TM_STB_up() { TM_PORT |= (1 << TM_STB); }

void TM_DIO_down() { TM_PORT &= ~(1 << TM_DIO); }

void TM_DIO_up() { TM_PORT |= (1 << TM_DIO); }

uint8_t TM_DIO_read() { return TM_PIN & (1 << TM_DIO) ? 0x01 : 0x00;}
