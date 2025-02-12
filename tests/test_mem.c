#include "tests.h"
#include <check.h>
#include "./../brick_game/tetris/include/tetris.h"
#include "./../brick_game/tetris/include/tetris.h"

START_TEST(test_mem) {
    Tetris_t* tetris = initTetris();
    tetris->destructor(tetris);
}
END_TEST

Suite* tetris_mem_suite(void) {
  Suite* s = suite_create("Tetris");
  TCase* tc_core = tcase_create("Core");
    
  tcase_add_test(tc_core, test_mem);
   
  suite_add_tcase(s, tc_core);
  return s;
}

