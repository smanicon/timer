#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "scheduler.h"

void scheduler_init() {
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  OCR2A = 156;

  TIMSK2 |= (1 << OCIE2A);
  sei();

  memset(task_list, 0, sizeof(task_list));
}

void scheduler_tick() {
  for (int i = 0; i < MAX_TASKS; i++) {
    task_t *t = &task_list[i];
    if (t->active && t->remaining_ticks > 0) {
      t->remaining_ticks--;
    }
  }
}

void scheduler_run() {
  set_sleep_mode(SLEEP_MODE_IDLE);
  while (true) {
    scheduler_run_next_tasks();
    sleep_mode();
  }
}

void scheduler_run_next_tasks() {
  for (int i = 0; i < MAX_TASKS; i++) {
    task_t *t = &task_list[i];
    if (t->active && t->enabled && t->remaining_ticks == 0) {
      t->task_fn(t->arg);
      t->remaining_ticks = t->period_ticks;
    }
  }
}

uint8_t scheduler_add_task(void (*task_fn)(int arg), int arg,
                           uint16_t period_ticks) {
  for (int i = 0; i < MAX_TASKS; i++) {
    task_t *t = &task_list[i];
    if (!t->active) {
      t->task_fn = task_fn;
      t->period_ticks = period_ticks;
      t->remaining_ticks = period_ticks;
      t->active = 1;
      t->enabled = 1;
      t->arg = arg;
      return i;
    }
  }
  return -1;
}

bool sheduler_is_tasck_active(uint8_t id) {
  if (id >= MAX_TASKS)
    return false;

  return task_list[id].active;
}

void scheduler_enable_task(uint8_t id) {
  if (!sheduler_is_tasck_active(id))
    return;
  task_list[id].enabled = true;
}

void scheduler_disable_task(uint8_t id) {
  if (!sheduler_is_tasck_active(id))
    return;
  task_list[id].enabled = false;
}

ISR(TIMER2_COMPA_vect) {
  scheduler_tick();
}
