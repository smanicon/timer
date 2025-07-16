#ifndef TM1638_H
#define TM1638_H

#include <stdint.h>
typedef enum { OUTPUT, INPUT } pin_direction;

typedef enum { HIGH, LOW } pin_value;

typedef struct {
  void (*set_mode)(pin_direction);
  void (*digital_write)(pin_value);
  pin_value (*digital_read)();
} pin_t;

typedef struct {
  pin_t clk;
  pin_t dio;
  pin_t stb;
  void (*delay)(uint8_t ms);
} TM1638_pin_t;

void TM1638_init(TM1638_pin_t *);
void TM_display_digit(TM1638_pin_t *pins, uint8_t pos, uint8_t digit);
void TM_display_4_digit(TM1638_pin_t *pins, uint8_t d1, uint8_t d2, uint8_t d3,
                        uint8_t d4);
void TM_display_on(TM1638_pin_t *);
void TM_display_off(TM1638_pin_t *);
#endif
