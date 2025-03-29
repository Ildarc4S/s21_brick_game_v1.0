#include "tests.h"

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(NULL);
  srunner_add_suite(sr, tetris_suite());
  srunner_add_suite(sr, tetris_fsm_suite());
  srunner_add_suite(sr, tetris_level_manager_suite());
  srunner_add_suite(sr, tetris_timer_suite());
  srunner_add_suite(sr, tetris_memory_utils_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
