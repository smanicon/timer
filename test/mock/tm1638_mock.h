#ifndef TM1638_FAKE_H
#define TM1638_FAKE_H

#include "tm1638.h"
#include <stdint.h>

typedef struct {
  pin_direction direction;
  pin_value value;
} pin_state;

typedef struct {
  pin_state stb;
  pin_state clk;
  pin_state dio;
} TM1638_pin_state;

TM1638_pin_t *init_TM1638_mock();
void get_TM_pin_state(TM1638_pin_state *);
void TEST_ASSERT_TM1638_TRAME(uint8_t expected[], int size);
void TEST_ASSERT_EQUAL_PIN_STATE(TM1638_pin_state *expected,
                                 TM1638_pin_state *actual);
void free_mock_TM1639();

#endif
