#include "scheduler.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct task_t task_t;

struct task_t {
  bool active;
  bool enabled;
  void (*task_fn)(void *);
  void *value;
  uint16_t period_tick;
  uint16_t remain_tick;
};

struct scheduler_t {
  task_t* tasks;
  int task_size;
};

scheduler_t *
scheduler_init(uint8_t task_size) {
  task_t *tasks = calloc(task_size, sizeof(task_t));
  scheduler_t* scheduler = malloc(sizeof(scheduler_t));

  scheduler->task_size = task_size;
  scheduler->tasks = tasks;
  return scheduler;
}

uint8_t scheduler_add_task(scheduler_t *s, void (*task_fn)(void *), void *v,
                           uint16_t tick) {
  for (int i = 0; i < s->task_size; i++) {
    task_t *t = &s->tasks[i];
    if (!t->active) {
      t->active = true;
      t->enabled = true;
      t->task_fn = task_fn;
      t->value = v;
      t->period_tick = tick;
      t->remain_tick = tick;
      return i;
    }
  }
  return -1;
}

void scheduler_tick(scheduler_t *s) {
  for (int i = 0; i < s->task_size; i++) {
    task_t *t = &s->tasks[i];
    if (t->active && t->enabled)
      t->remain_tick--;
  }
}

void scheduler_run_next_tasks(scheduler_t *s) {
  for (int i = 0; i < s->task_size; i++) {
    task_t *t = &s->tasks[i];
    if (t->active && t->enabled && t->remain_tick == 0) {
      t->remain_tick = t->period_tick;
      t->task_fn(t->value);
    }
  }
}

void scheduler_disable_task(scheduler_t *s, uint8_t id) {
  task_t *t = &s->tasks[id];
  t->enabled = false;
}

void scheduler_enable_task(scheduler_t *s, uint8_t id) {
  task_t *t = &s->tasks[id];
  t->enabled = true;
}
