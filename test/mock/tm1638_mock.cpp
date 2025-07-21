#include "tm1638_mock.hpp"
#include "TrameManager.hpp"
#include "tm1638.h"
#include "gtest/gtest.h"
#include <ostream>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

TM1638_pin_t *_tm1638_pin;
pin_state stb;
pin_state clk;
pin_state dio;

TrameManager _trames;

bool rising_edge(pin_state pin, pin_value value) {
  return pin.value == LOW && value == HIGH;
}

bool falling_edge(pin_state pin, pin_value value) {
  return pin.value == HIGH && value == LOW;
}

void stb_digital_write(pin_value v) {
  if (falling_edge(stb, v)) {
    _trames.new_trame();
  }
  stb.value = v;
}

void clk_digital_write(pin_value v) {
  if (rising_edge(clk, v)) {
    _trames.write_bit(dio.value);
  }

  clk.value = v;
}

void dio_digital_write(pin_value v) { dio.value = v; }
pin_value dio_digital_read() { return LOW; }

TM1638_pin_t *init_TM1638_mock() {
  _trames.new_trame();

  _tm1638_pin = new TM1638_pin_t;
  *_tm1638_pin = {
    .clk{.set_mode = [](pin_direction d) { clk.direction = d; },
       .digital_write = clk_digital_write,
       .digital_read = []() { return LOW; }},
    .dio{.set_mode = [](pin_direction d) { dio.direction = d; },
       .digital_write = dio_digital_write,
       .digital_read = dio_digital_read},
    .stb{.set_mode = [](pin_direction d) { stb.direction = d; },
       .digital_write = stb_digital_write,
       .digital_read = []() { return LOW; }},
    .delay = [](uint8_t ms) {}};

  return _tm1638_pin;
}

void free_mock_TM1639() { free(_tm1638_pin); }

bool operator==(const pin_state &p1, const pin_state &p2)
{
  return p1.value == p2.value && p1.direction == p2.direction;
}

std::ostream &operator<<(std::ostream &os, const pin_state &p) {
  std::string value = p.value == HIGH ? "High" : "Low";
  std::string direction = p.direction == INPUT ? "Input" : "Output";
  return os << direction << ":" << value;
}

::testing::AssertionResult validate_pins_state(const char *expr1,
                                            const TM1638_pin_state *expected) {
  if (expected->stb == stb && expected->clk == clk && expected->dio == dio) {
    return ::testing::AssertionSuccess();
  }

  return ::testing::AssertionFailure()
         << "pin state expected " << expr1 << std::endl
         << "- actual:   stb[" << stb << "], clk[" << clk << "], dio[" << dio << "]" << std::endl
         << "- expected: stb[" << expected->stb << "], clk[" << expected->clk << "], dio[" << expected->dio << "]" << std::endl;
}

::testing::AssertionResult validate_last_trame(const char *expr, const std::vector<uint8_t> &expected) {
  Trame expected_t(expected);
  if (expected_t == _trames.lastTrame()) {
    return ::testing::AssertionSuccess();
  }

  return ::testing::AssertionFailure()
    << "last trame expected " << expr << std::endl
    << "- actual: " << _trames.lastTrame() << std::endl
    << "- expected: " << expected_t << std::endl;
}
