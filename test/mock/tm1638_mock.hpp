#ifndef TM1638_FAKE_H
#define TM1638_FAKE_H

#include "gtest/gtest.h"
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
void free_mock_TM1639();
::testing::AssertionResult validate_pins_state(const char *,
                                               const TM1638_pin_state *);
::testing::AssertionResult validate_last_trame(const char *,
                                               const std::vector<uint8_t> &);
#endif
