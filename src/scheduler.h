#include <stdint.h>
#include <stdbool.h>

#ifndef SHEDULER_H
#define SHEDULER_H

#define MAX_TASKS 5
#define TICK_MS 100

typedef struct {
  void (*task_fn)(int arg);
  uint16_t period_ticks;
  uint16_t remaining_ticks;
  uint8_t active;
  uint8_t enabled;
  int arg;
} task_t;

task_t task_list[MAX_TASKS];

void scheduler_init();
void scheduler_tick();
void scheduler_run();
void scheduler_run_next_tasks();
uint8_t scheduler_add_task(void (*task_fn)(int arg), int arg, uint16_t period_ticks);
bool sheduler_is_tasck_active(uint8_t id);
void scheduler_enable_task(uint8_t id);
void scheduler_disable_task(uint8_t id);
#endif
