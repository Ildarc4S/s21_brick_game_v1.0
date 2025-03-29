#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "./../../brick_game/tetris/include/level_manager.h"
#include "./../../brick_game/tetris/include/memory_utils.h"
#include "./../../brick_game/tetris/include/tetris.h"
#include "./../../brick_game/tetris/include/timer.h"
#include "./../../brick_game/tetris/include/utils.h"

Suite* tetris_suite(void);
Suite* tetris_fsm_suite(void);
Suite* tetris_level_manager_suite(void);
Suite* tetris_timer_suite(void);
Suite* tetris_memory_utils_suite(void);

#endif  // TESTS_H
