
#include <stdint.h>
#include <util/delay.h>

#include "motherboard.h"
#include "tm1638.h"

const uint8_t segment_map[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void TM_write_bit(uint8_t bit) {
  if (bit)
    TM_DIO_up();
  else
    TM_DIO_down();

  TM_clock_down();
  _delay_us(1);
  TM_clock_up();
  _delay_us(1);
}

void TM_write_byte(uint8_t data) {
  TM_set_DIO_output();
  for (uint8_t i = 0; i < 8; i++) {
    TM_write_bit(data & 0x01);
    data >>= 1;
  }
}

uint8_t TM_read_bit() {
  TM_clock_down();
  _delay_us(1);

  uint8_t data = TM_DIO_read();

  TM_clock_up();
  _delay_us(1);

  return data;
}

uint8_t TM_read_byte() {
  TM_set_DIO_input();
  uint8_t result = 0x00;
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t data = TM_read_bit();
    result |= (data << i);
  }

  return result;
}

void TM_send_command(uint8_t command) {
  TM_STB_down();
  TM_write_byte(command);
  TM_STB_up();
}

void TM_init() {
  TM_init_port();
  TM_send_command(0x40);

  TM_STB_down();
  TM_write_byte(0xC0);
  for (uint8_t i = 0; i < 16; i++) {
    TM_write_byte(0x00);
  }
  TM_STB_up();
  TM_send_command(0x88);
}

void TM_display_digit(uint8_t pos, uint8_t num) {
  if (pos > 7 || num > 9)
    return;

  TM_STB_down();
  TM_write_byte(0xC0 + (pos << 1));
  TM_write_byte(segment_map[num]);
  TM_STB_up();
}

void TM_display_4_digit(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4) {
  TM_send_command(0x40);

  int data[] = {
    segment_map[d1],
    segment_map[d2],
    segment_map[d3],
    segment_map[d4]
  };

  TM_STB_down();
  TM_write_byte(0xC0);
  for (uint8_t i = 0; i < 4; i++) {
    TM_write_byte(data[i]);
    TM_write_byte(0x00);
  }
  TM_STB_up();
  TM_send_command(0x88);
}

void TM_display_off() {
  TM_send_command(0x80);
}

void TM_display_on() {
  TM_send_command(0x88);
}

uint8_t TM_button_read() {
  TM_STB_down();
  TM_write_byte(0x42);
  uint8_t button = TM_read_byte();
  TM_STB_up();
  return button;
}
