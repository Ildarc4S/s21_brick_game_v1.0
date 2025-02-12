#include "tests.h"
#include <check.h>
#include "./../brick_game/tetris/include/timer.h"


START_TEST(test_timer_init) {
    Timer_t timer = constructorTimer();
    
    ck_assert_int_eq(timer.getTick(&timer), 1000);
    
    ck_assert(timer.current_time.tv_sec != 0);
    ck_assert(timer.last_time.tv_sec != 0);
}
END_TEST

START_TEST(test_update_current_time) {
    Timer_t timer = constructorTimer();
    struct timeval initial_last_time = timer.last_time;
    
    timer.updateCurrenTime(&timer);
    
    ck_assert(timer.last_time.tv_sec == initial_last_time.tv_sec);
    ck_assert(timer.last_time.tv_usec == initial_last_time.tv_usec);
    ck_assert(timer.current_time.tv_sec >= initial_last_time.tv_sec);
}
END_TEST

START_TEST(test_update_last_time) {
    Timer_t timer = constructorTimer();
    timer.updateCurrenTime(&timer);  // Обновляем current_time
    struct timeval initial_current_time = timer.current_time;
    
    timer.updateLastTime(&timer);
    
    ck_assert(timer.last_time.tv_sec == initial_current_time.tv_sec);
    ck_assert(timer.last_time.tv_usec == initial_current_time.tv_usec);
}
END_TEST

START_TEST(test_time_diff) {
    Timer_t timer = constructorTimer();
    
    timer.last_time.tv_sec = 1;
    timer.last_time.tv_usec = 500000;  // 0.5 second 
    
    long diff = timer.calcDiff(&timer);
    ck_assert_int_ne(diff, 0);
}
END_TEST

START_TEST(test_tick_set_get) {
    Timer_t timer = constructorTimer();
    timer.setTick(&timer, 2000);
    ck_assert_int_eq(timer.getTick(&timer), 2000);
}
END_TEST

Suite *tetris_timer_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Tetris Timer");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_timer_init);
    tcase_add_test(tc_core, test_update_current_time);
    tcase_add_test(tc_core, test_update_last_time);
    tcase_add_test(tc_core, test_time_diff);
    tcase_add_test(tc_core, test_tick_set_get);
    
    suite_add_tcase(s, tc_core);
    return s;
}


