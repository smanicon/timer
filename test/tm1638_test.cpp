#include "tm1638.h"
#include "tm1638_mock.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <map>
#include <stdbool.h>
#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>

void tearDown() { free_mock_TM1639(); }

class TM1638 : public ::testing::Test {
protected:
  TM1638_pin_t *tm;

  void SetUp() override {
    tm = init_TM1638_mock();

  }

  void TearDown() override {
    free_mock_TM1639();
  }
};

TEST_F(TM1638, should_put_all_pin_at_output_and_high_level_when_init) {
  TM1638_pin_state actual;

  TM1638_pin_state expected = {
      .stb = {OUTPUT, HIGH}, .clk = {OUTPUT, HIGH}, .dio = {OUTPUT, HIGH}};

  EXPECT_PRED_FORMAT1(validate_pins_state, &expected);
}

TEST_F(TM1638, should_send_trame_to_display_on) {
  TM_display_on(tm);

  std::vector<uint8_t> expected = {0X88};
  EXPECT_PRED_FORMAT1(validate_last_trame, expected);
}

TEST_F(TM1638, should_send_trame_to_display_off) {
  TM_display_off(tm);

  std::vector<uint8_t> expected = {0X80};
  EXPECT_PRED_FORMAT1(validate_last_trame, expected);
}

class TM1638_Display
    : public TM1638,
      public ::testing::WithParamInterface<std::tuple<int, int>> {
protected:
  std::map<int, uint8_t> address = {{0, 0xC0}, {1, 0xC2}, {2, 0xC4}, {3, 0xC6}};

  std::map<int, uint8_t> display = {
      {0, 0x3F}, {1, 0x06}, {2, 0x5B}, {3, 0x4F}, {4, 0x66},
      {5, 0x6D}, {6, 0x7D}, {7, 0x07}, {8, 0x7F}, {9, 0x6F}
  };
};

TEST_P(TM1638_Display, should_print_right_number_at_right_digit) {
  auto [digit, number] = GetParam();
  TM_display_digit(tm, digit, number);
  std::vector<uint8_t> expected = {address[digit], display[number]};
  EXPECT_PRED_FORMAT1(validate_last_trame, expected);
}

std::vector<std::tuple<int, int>> generate_pairs_digit_number() {
  std::vector<std::tuple<int, int>> pairs;
  for (int a = 0; a <= 3; ++a) {
    for (int b = 0; b <= 9; ++b) {
      pairs.emplace_back(a, b);
    }
  }
  return pairs;
};

INSTANTIATE_TEST_SUITE_P(
    all_digits,
    TM1638_Display,
    ::testing::ValuesIn(generate_pairs_digit_number()),
    [](const testing::TestParamInfo<std::tuple<int, int>> &info) {
      int digit = std::get<0>(info.param);
      int number = std::get<1>(info.param);
      return "should_print_" + std::to_string(number) + "_on_digit_" + std::to_string(digit);
    }
);


// TEST(TM1638, should_send_trame_to_display_1_2_3_4_on_all_digit) {
//   TM_display_4_digit(tm, 1, 2, 3, 4);
//
//   uint8_t expected[] = {0x40, 0xC0, 0x06, 0x00, 0x5B, 0x00,
//                         0x4F, 0x00, 0x66, 0x00, 0x88};
// }

