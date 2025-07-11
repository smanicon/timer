#include "tm1638.h"
#include "scheduler.h"
#include <stdint.h>

typedef struct {
  int counter;
  bool run;
} timer_t;

typedef struct {
  uint8_t id_counter;
  int *counter;
} counter_t;

void decrement_counter(int arg) {
  counter_t *counter = (counter_t *)arg;

  if(*counter->counter) {
    (*counter->counter) --;
  } else {
    scheduler_disable_task(counter->id_counter);
  }
}

typedef struct {
  timer_t *timer;
  bool blink;
} display_t;

void display_counter(int arg) {
  display_t *display = (display_t *) arg;

  if(display->timer->run || ! display->blink) {
    int *counter = &display->timer->counter;

    int seconde = *counter % 60;
    int minute = *counter / 60;

    TM_display_4_digit(
        minute / 10,
        minute % 10,
        seconde / 10,
        seconde % 10
    );
  } else if (! display->timer->run && display->blink) {
    TM_display_off();
  }
  display->blink = ! display->blink;
}

typedef struct {
  bool *run;
  uint8_t id_counter;
} input_t;

void input_reader(int arg) {
  input_t *input = (input_t*) arg;

  if(TM_button_read()) {
    *input->run = true;
    scheduler_enable_task(input->id_counter);
  }
}

int main() {
  TM_init();
  scheduler_init();

  timer_t timer = {160, false};

  counter_t counter = {0, &timer.counter};
  counter.id_counter = scheduler_add_task(decrement_counter, (int)&counter, 100);
  scheduler_disable_task(counter.id_counter);

  display_t display = {&timer, false};
  scheduler_add_task(display_counter, (int) &display, 50);

  input_t input = {&timer.run, counter.id_counter};
  scheduler_add_task(input_reader, (int) &input, 10);

  scheduler_run();
  return 0;
}
