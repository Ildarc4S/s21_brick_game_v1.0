#include <check.h>

#include "tests.h"

START_TEST(test_timer_init) {
  Timer_t timer = initTimer();

  ck_assert_int_eq(timer.tick, 1000);
  ck_assert(timer.current_time.tv_sec > 0);
  ck_assert(timer.last_time.tv_sec > 0);
}
END_TEST

START_TEST(test_update_current_time) {
  Timer_t timer = initTimer();
  struct timeval initial_last_time = timer.last_time;

  timer.updateCurrenTime(&timer);

  ck_assert(timer.last_time.tv_sec == initial_last_time.tv_sec);
  ck_assert(timer.last_time.tv_usec == initial_last_time.tv_usec);
  ck_assert(timer.current_time.tv_sec >= initial_last_time.tv_sec);
}
END_TEST

START_TEST(test_update_last_time) {
  Timer_t timer = initTimer();
  timer.updateCurrenTime(&timer);
  struct timeval initial_current_time = timer.current_time;

  timer.updateLastTime(&timer);

  ck_assert(timer.last_time.tv_sec == initial_current_time.tv_sec);
  ck_assert(timer.last_time.tv_usec == initial_current_time.tv_usec);
}
END_TEST

START_TEST(test_time_diff) {
  Timer_t timer = initTimer();

  timer.last_time.tv_sec = timer.current_time.tv_sec - 1;
  timer.last_time.tv_usec = timer.current_time.tv_usec;

  long diff = timer.calcDiff(&timer);
  ck_assert_int_eq(diff, 1000);
}
END_TEST

START_TEST(test_tick_modification) {
  Timer_t timer = initTimer();

  timer.tick = 2000;
  ck_assert_int_eq(timer.tick, 2000);
}
END_TEST

Suite* tetris_timer_suite(void) {
  Suite* s = suite_create("Tetris Timer");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_timer_init);
  tcase_add_test(tc_core, test_update_current_time);
  tcase_add_test(tc_core, test_update_last_time);
  tcase_add_test(tc_core, test_time_diff);
  tcase_add_test(tc_core, test_tick_modification);

  suite_add_tcase(s, tc_core);
  return s;
}
