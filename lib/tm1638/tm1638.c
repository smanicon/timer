#include "tm1638.h"
#include <stdint.h>

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

void TM_write_bit(TM1638_pin_t *pins, uint8_t bit) {
  if (bit)
    pins->dio.digital_write(HIGH);
  else
    pins->dio.digital_write(LOW);

  pins->clk.digital_write(LOW);
  pins->delay(1);
  pins->clk.digital_write(HIGH);
  pins->delay(1);
}

void TM_write_byte(TM1638_pin_t *pins, uint8_t data) {
  pins->dio.set_mode(OUTPUT);
  for (uint8_t i = 0; i < 8; i++) {
    TM_write_bit(pins, data & 0x01);
    data >>= 1;
  }
}

void TM_send_command(TM1638_pin_t *pins, uint8_t command) {
  pins->stb.digital_write(LOW);
  TM_write_byte(pins, command);
  pins->stb.digital_write(HIGH);
}

void TM1638_init(TM1638_pin_t *pins) {
  pins->stb.set_mode(OUTPUT);
  pins->stb.digital_write(HIGH);
  pins->clk.set_mode(OUTPUT);
  pins->clk.digital_write(HIGH);
  pins->dio.set_mode(OUTPUT);
  pins->dio.digital_write(HIGH);
}

void TM_display_off(TM1638_pin_t *pins) { TM_send_command(pins, 0x80); }

void TM_display_on(TM1638_pin_t *pins) { TM_send_command(pins, 0x88); }

void TM_display_digit(TM1638_pin_t *pins, uint8_t pos, uint8_t num) {
  if (pos > 7 || num > 9)
    return;

  pins->stb.digital_write(LOW);
  TM_write_byte(pins, 0xC0 + (pos << 1));
  TM_write_byte(pins, segment_map[num]);
  pins->stb.digital_write(HIGH);
}

void TM_display_4_digit(TM1638_pin_t *pins, uint8_t d1, uint8_t d2, uint8_t d3,
                        uint8_t d4) {
  TM_send_command(pins, 0x40);

  int data[] = {segment_map[d1], segment_map[d2], segment_map[d3],
                segment_map[d4]};

  pins->stb.digital_write(LOW);
  TM_write_byte(pins, 0xC0);
  for (uint8_t i = 0; i < 4; i++) {
    TM_write_byte(pins, data[i]);
    TM_write_byte(pins, 0x00);
  }
  pins->stb.digital_write(HIGH);
  TM_send_command(pins, 0x88);
}
