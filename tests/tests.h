#ifndef TESTS_H
#define TESTS_H

#include <check.h>

Suite* tetris_suite(void);
Suite* tetris_fsm_suite(void);
Suite* tetris_level_manager_suite(void);
Suite* tetris_timer_suite(void);

#endif  // TESTS_H
