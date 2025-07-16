#include "unity_internals.h"
#include <stdbool.h>
#include <stdint.h>
#include <unity.h>
#include "tm1638.h"
#include "tm1638_mock.h"

TM1638_pin_t *tm;

void setUp() {
  tm = init_TM1638_mock();
  TM1638_init(tm);
}
void tearDown() {
  free_mock_TM1639();
}

void should_put_all_pin_at_output_and_high_level_when_init() {
  TM1638_pin_state actual;
  get_TM_pin_state(&actual);

  TM1638_pin_state expected = {
      .clk = {OUTPUT, HIGH}, .stb = {OUTPUT, HIGH}, .dio = {OUTPUT, HIGH}};

  TEST_ASSERT_EQUAL_PIN_STATE(&expected, &actual);
}

void should_send_trame_to_display_on() {
  TM_display_on(tm);

  uint8_t expected[] = {0x88};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_send_trame_to_display_off() {
  TM_display_off(tm);

  uint8_t expected[] = {0x80};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_send_trame_to_display_8_on_digit_1() {
  TM_display_digit(tm, 0, 8);

  uint8_t expected[] = {0xC0, 0x7F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_send_trame_to_display_8_on_digit_2() {
  TM_display_digit(tm, 1, 8);

  uint8_t expected[] = {0xC2, 0x7F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_send_trame_to_display_8_on_digit_3() {
  TM_display_digit(tm, 2, 8);

  uint8_t expected[] = {0xC4, 0x7F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_send_trame_to_display_8_on_digit_4() {
  TM_display_digit(tm, 3, 8);

  uint8_t expected[] = {0xC6, 0x7F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_send_trame_to_display_1_2_3_4_on_all_digit() {
  TM_display_4_digit(tm, 1, 2, 3, 4);

  uint8_t expected[] = {0x40, 0xC0, 0x06, 0x00, 0x5B, 0x00, 0x4F, 0x00, 0x66, 0x00, 0x88};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_0() {
  TM_display_digit(tm, 0, 0);

  uint8_t expected[] = {0xC0, 0x3F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_1() {
  TM_display_digit(tm, 0, 1);

  uint8_t expected[] = {0xC0, 0x06};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_2() {
  TM_display_digit(tm, 0, 2);

  uint8_t expected[] = {0xC0, 0x5B};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_3() {
  TM_display_digit(tm, 0, 3);

  uint8_t expected[] = {0xC0, 0x4F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_4() {
  TM_display_digit(tm, 0, 4);

  uint8_t expected[] = {0xC0, 0x66};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_5() {
  TM_display_digit(tm, 0, 5);

  uint8_t expected[] = {0xC0, 0x6D};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_6() {
  TM_display_digit(tm, 0, 6);

  uint8_t expected[] = {0xC0, 0x7D};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_7() {
  TM_display_digit(tm, 0, 7);

  uint8_t expected[] = {0xC0, 0x07};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_8() {
  TM_display_digit(tm, 0, 8);

  uint8_t expected[] = {0xC0, 0x7F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

void should_display_9() {
  TM_display_digit(tm, 0, 9);

  uint8_t expected[] = {0xC0, 0x6F};
  TEST_ASSERT_TM1638_TRAME(expected, sizeof(expected));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_put_all_pin_at_output_and_high_level_when_init);
  RUN_TEST(should_send_trame_to_display_on);
  RUN_TEST(should_send_trame_to_display_off);
  RUN_TEST(should_send_trame_to_display_8_on_digit_1);
  RUN_TEST(should_send_trame_to_display_8_on_digit_2);
  RUN_TEST(should_send_trame_to_display_8_on_digit_3);
  RUN_TEST(should_send_trame_to_display_8_on_digit_4);
  RUN_TEST(should_send_trame_to_display_1_2_3_4_on_all_digit);
  RUN_TEST(should_display_0);
  RUN_TEST(should_display_1);
  RUN_TEST(should_display_2);
  RUN_TEST(should_display_3);
  RUN_TEST(should_display_4);
  RUN_TEST(should_display_5);
  RUN_TEST(should_display_6);
  RUN_TEST(should_display_7);
  RUN_TEST(should_display_8);
  RUN_TEST(should_display_9);

  return UNITY_END();
}
