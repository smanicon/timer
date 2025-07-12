#include "unity.h"
#include "unity_internals.h"
#include <stdbool.h>
#include <stdint.h>


void setUp() {}

void tearDown() {}

#include "scheduler.h"

void task(void *v) {
  int *data = (int *)v;
  (*data)++;
}

void should_run_task_when_remain_tick_reach_0() {
  int runned = 0;
  scheduler_t *s = scheduler_init(1);
  scheduler_add_task(s, task, &runned, 1);

  scheduler_tick(s);
  scheduler_run_next_tasks(s);

  TEST_ASSERT_EQUAL(runned, 1);
}

void should_run_task_two_times_when_remain_tick_reach_0_two_times() {
  int runned = 0;
  scheduler_t *s = scheduler_init(1);
  scheduler_add_task(s, task, &runned, 1);

  for (int i = 0; i < 2; i++) {
    scheduler_tick(s);
    scheduler_run_next_tasks(s);
  }

  TEST_ASSERT_EQUAL(runned, 2);
}

void should_not_run_task_when_tick_don_t_reach_0() {
  int runned = 0;
  scheduler_t *s = scheduler_init(1);
  scheduler_add_task(s, task, &runned, 2);

  scheduler_tick(s);
  scheduler_run_next_tasks(s);

  TEST_ASSERT_EQUAL(runned, 0);
}

void should_run_task_one_time_on_restart_tick() {
  int runned = 0;
  scheduler_t *s = scheduler_init(1);
  scheduler_add_task(s, task, &runned, 2);

  for (int i = 0; i < 3; i++) {
    scheduler_tick(s);
    scheduler_run_next_tasks(s);
  }

  TEST_ASSERT_EQUAL(runned, 1);
}

void should_run_tasks_concurrently() {
  int runned = 0;
  scheduler_t *s = scheduler_init(2);
  scheduler_add_task(s, task, &runned, 1);
  scheduler_add_task(s, task, &runned, 1);

  scheduler_tick(s);
  scheduler_run_next_tasks(s);

  TEST_ASSERT_EQUAL(runned, 2);
}

void should_add_task_when_max_task_isn_t_reached() {
  scheduler_t *s = scheduler_init(1);
  uint8_t addedTask = scheduler_add_task(s, task, 0, 1);
  TEST_ASSERT_NOT_EQUAL_UINT8(-1, addedTask);
}

void should_not_add_task_when_max_task_is_reached() {
  scheduler_t *s = scheduler_init(1);
  scheduler_add_task(s, task, 0, 1);
  uint8_t addedTask = scheduler_add_task(s, task, 0, 1);
  TEST_ASSERT_EQUAL_UINT8(-1, addedTask);
}

void should_not_run_task_if_it_is_disabled() {
  int runner = 0;
  scheduler_t *s = scheduler_init(1);
  int id = scheduler_add_task(s, task, &runner, 1);
  scheduler_disable_task(s, id);

  scheduler_tick(s);
  scheduler_run_next_tasks(s);

  TEST_ASSERT_EQUAL(0, runner);
}

void should_run_task_when_it_is_reenabled() {
  int runner = 0;
  scheduler_t *s = scheduler_init(1);
  int id = scheduler_add_task(s, task, &runner, 1);
  scheduler_disable_task(s, id);
  scheduler_enabled_task(s, id);

  scheduler_tick(s);
  scheduler_run_next_tasks(s);

  TEST_ASSERT_EQUAL(1, runner);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_run_task_when_remain_tick_reach_0);
  RUN_TEST(should_run_task_two_times_when_remain_tick_reach_0_two_times);
  RUN_TEST(should_not_run_task_when_tick_don_t_reach_0);
  RUN_TEST(should_run_task_one_time_on_restart_tick);
  RUN_TEST(should_run_tasks_concurrently);
  RUN_TEST(should_add_task_when_max_task_isn_t_reached);
  RUN_TEST(should_not_add_task_when_max_task_is_reached);
  RUN_TEST(should_not_run_task_if_it_is_disabled);
  RUN_TEST(should_run_task_when_it_is_reenabled);
  return UNITY_END();
}
