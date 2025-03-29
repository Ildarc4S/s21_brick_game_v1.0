#include <check.h>

#include "tests.h"

START_TEST(test_score_basic) {
  Score_t score = initScore();
  ck_assert_int_eq(score.score, 0);

  score.score = 500;
  ck_assert_int_eq(score.score, 500);
}
END_TEST

START_TEST(test_score_line_conversion) {
  Score_t score = initScore();

  score.convertLineCountToScore(&score, 1);
  ck_assert_int_eq(score.score, 100);

  score.convertLineCountToScore(&score, 2);
  ck_assert_int_eq(score.score, 400);

  score.convertLineCountToScore(&score, 3);
  ck_assert_int_eq(score.score, 1100);

  score.convertLineCountToScore(&score, 4);
  ck_assert_int_eq(score.score, 2600);
}
END_TEST

START_TEST(test_level_basic) {
  Level_t level = initLevel();
  ck_assert_int_eq(level.level, 1);

  level.level = 5;
  ck_assert_int_eq(level.level, 5);
}
END_TEST

START_TEST(test_level_progression) {
  Level_t level = initLevel();

  level.score.score = 600;
  level.updateLevel(&level);
  ck_assert_int_eq(level.level, 2);

  level.score.score = 2400;
  level.updateLevel(&level);
  ck_assert_int_eq(level.level, 5);

  level.score.score = 60000;
  level.updateLevel(&level);
  ck_assert_int_eq(level.level, 10);
}
END_TEST

Suite* tetris_level_manager_suite(void) {
  Suite* s = suite_create("Tetris Level Manager");

  TCase* tc_score = tcase_create("Tetris Score");
  tcase_add_test(tc_score, test_score_basic);
  tcase_add_test(tc_score, test_score_line_conversion);
  suite_add_tcase(s, tc_score);

  TCase* tc_level = tcase_create("Tetris Level");
  tcase_add_test(tc_level, test_level_basic);
  tcase_add_test(tc_level, test_level_progression);
  suite_add_tcase(s, tc_level);

  return s;
}
