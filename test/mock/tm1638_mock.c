#include "tm1638_mock.h"
#include "tm1638.h"
#include "unity.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TM1638_pin_t *tm1638_pin;

pin_state clk;
pin_state stb;
pin_state dio;

uint8_t trame[255];
uint8_t trame_index = 0;
uint8_t current_bit = 0;

pin_value nop_read_value() { return LOW;}
void wait_nop(uint8_t t) {}

void stb_set_direction(pin_direction d) {
  stb.direction = d;
}

void stb_set_value(pin_value v) {
  if(stb.direction == OUTPUT)
    stb.value = v;
}

void clk_set_direction(pin_direction d) { stb.direction = d; }

void clk_set_value(pin_value v) {
  if(clk.direction == INPUT || stb.direction == INPUT)
    return;

  if(clk.value == LOW && v == HIGH && stb.value == LOW) {
    if(current_bit == 8) {
      trame_index ++;
      current_bit = 0;
    }
    if (dio.value == HIGH)
      trame[trame_index] |= (1 << current_bit);
    current_bit++;
  }
  clk.value = v;
}

void dio_set_direction(pin_direction d) {
  dio.direction = d;
}

void dio_set_value(pin_value v) {
  if (dio.direction == OUTPUT)
    dio.value = v;
}

pin_value dio_read_value() { return LOW;}

TM1638_pin_t *init_TM1638_mock() {
  pin_t stb_pin = {stb_set_direction, stb_set_value, nop_read_value};
  pin_t clk_pin = {clk_set_direction, clk_set_value, nop_read_value};
  pin_t dio_pin = {dio_set_direction, dio_set_value, dio_read_value};

  tm1638_pin = malloc(sizeof(TM1638_pin_t));
  tm1638_pin->clk = clk_pin;
  tm1638_pin->dio = dio_pin;
  tm1638_pin->stb = stb_pin;
  tm1638_pin->delay = wait_nop;

  memset(trame, 0, 255);
  trame_index = 0;
  current_bit = 0;

  return tm1638_pin;
}

void get_TM_pin_state(TM1638_pin_state *s) {
  s->clk = clk;
  s->stb = stb;
  s->dio = dio;
}

void print_uint8_array(const char *label, const uint8_t *array, size_t len) {
  printf("%s: ", label);
  for (size_t i = 0; i < len; ++i) {
    printf("0x%02X ", array[i]);
  }
  printf("\n");
}

void convert_to_hex(char* hex, uint8_t* value, size_t len)
{
  char t[6];
  for (size_t i = 0; i < len; i++) {
    sprintf(t, "0x%02X ", value[i]);
    strcat(hex, t);
  }
}

void TEST_ASSERT_TM1638_TRAME(uint8_t expected[], int size) {
  char expected_hex[255];
  memset(expected_hex, 0, sizeof(expected_hex));
  convert_to_hex(expected_hex, expected, size);

  char actual_hex[255];
  memset(actual_hex, 0, sizeof(actual_hex));
  convert_to_hex(actual_hex, trame, trame_index + 1);

  char message[355];
  sprintf(message, " Expected: %s, Actual: %s", expected_hex, actual_hex);
  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected, trame, size, message);
}

void TEST_ASSERT_EQUAL_PIN_STATE(TM1638_pin_state *expected,
                                 TM1638_pin_state *actual) {
  TEST_ASSERT_EQUAL_MESSAGE(expected->clk.value, actual->clk.value, "clk value");
  TEST_ASSERT_EQUAL_MESSAGE(expected->clk.direction, actual->clk.direction, "clk direction");

  TEST_ASSERT_EQUAL_MESSAGE(expected->dio.value, actual->dio.value, "dio value");
  TEST_ASSERT_EQUAL_MESSAGE(expected->dio.direction, actual->dio.direction, "dio direction");

  TEST_ASSERT_EQUAL_MESSAGE(expected->stb.value, actual->stb.value, "stb value");
  TEST_ASSERT_EQUAL_MESSAGE(expected->stb.direction, actual->stb.direction, "stb direction");
}

void free_mock_TM1639() {
  free(tm1638_pin);
}

