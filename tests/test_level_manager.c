#include "tests.h"
#include <check.h>
#include "./../brick_game/tetris/include/level_manager.h"

START_TEST(test_score_basic) {
    Score_t score = constructorScore();
    ck_assert_int_eq(score.getScore(&score), 0);
    
    score.setScore(&score, 500);
    ck_assert_int_eq(score.getScore(&score), 500);
}
END_TEST

START_TEST(test_score_line_conversion) {
    Score_t score = constructorScore();
    
    score.convertLineCountToScore(&score, 1);
    ck_assert_int_eq(score.getScore(&score), 100);
    
    score.convertLineCountToScore(&score, 3);
    ck_assert_int_eq(score.getScore(&score), 800);
    
    score.convertLineCountToScore(&score, 4);
    ck_assert_int_eq(score.getScore(&score), 2300);
    
    score.convertLineCountToScore(&score, 6);
    ck_assert_int_eq(score.getScore(&score), 2300);

    score.convertLineCountToScore(&score, 0);
    ck_assert_int_eq(score.getScore(&score), 2300);
}
END_TEST

START_TEST(test_level_basic) {
    Level_t level = constructorLevel();
    ck_assert_int_eq(level.getLevel(&level), 1);
    
    level.setLevel(&level, 5);
    ck_assert_int_eq(level.getLevel(&level), 5);
}
END_TEST

START_TEST(test_level_score_management) {
    Level_t level = constructorLevel();
    Score_t bonus = constructorScore();
    bonus.setScore(&bonus, 300);
    
    level.setScore(&level, &bonus);
    ck_assert_int_eq(level.score.getScore(&level.score), 300);
    
    bonus.setScore(&bonus, 500);
    level.setScore(&level, &bonus);
    ck_assert_int_eq(level.score.getScore(&level.score), 800);
}
END_TEST

START_TEST(test_level_progression) {
    Level_t level = constructorLevel();
    
    // Уровень 2: 600 очков
    level.score.setScore(&level.score, 600);
    level.updateLevel(&level);
    ck_assert_int_eq(level.getLevel(&level), 2);
    
    // Уровень 5: 2400 очков
    level.score.setScore(&level.score, 2400);
    level.updateLevel(&level);
    ck_assert_int_eq(level.getLevel(&level), 5);
    
    // Максимальный уровень
    level.score.setScore(&level.score, 60000);
    level.updateLevel(&level);
    ck_assert_int_eq(level.getLevel(&level), 10);
}
END_TEST

Suite* level_manager_suite(void) {
    Suite* s = suite_create("Level Manager");
    
    TCase* tc_score = tcase_create("Score");
    tcase_add_test(tc_score, test_score_basic);
    tcase_add_test(tc_score, test_score_line_conversion);
    suite_add_tcase(s, tc_score);
    
    TCase* tc_level = tcase_create("Level");
    tcase_add_test(tc_level, test_level_basic);
    tcase_add_test(tc_level, test_level_score_management);
    tcase_add_test(tc_level, test_level_progression);
    suite_add_tcase(s, tc_level);
    
    return s;
}
