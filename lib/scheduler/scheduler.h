
#include <stdbool.h>
#include <stdint.h>

#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct scheduler_t scheduler_t;
scheduler_t *scheduler_init(uint8_t task_max);
uint8_t scheduler_add_task(scheduler_t *s, void (*task_fn)(void *), void *v, uint16_t tick);
void scheduler_tick(scheduler_t *s);
void scheduler_run_next_tasks(scheduler_t *s);
void scheduler_disable_task(scheduler_t *, uint8_t id);
void scheduler_enable_task(scheduler_t *, uint8_t id);

#endif
