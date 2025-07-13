#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

scheduler_t *scheduler = 0;

void TIMER_init(scheduler_t *s) {
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  OCR2A = 156;
  TIMSK2 |= (1 << OCIE2A);

  scheduler = s;

  sei();
}

void TIMER_loop() {
  if(! scheduler)
    return;

  set_sleep_mode(SLEEP_MODE_IDLE);
  while (1) {
    scheduler_run_next_tasks(scheduler);
    sleep_mode();
  }
}

ISR(TIMER2_COMPA_vect) {
  if(scheduler) {
    scheduler_tick(scheduler);
  }
}
