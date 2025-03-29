#include <check.h>

#include "tests.h"

START_TEST(test_newField_creates_valid_field) {
  int width = 10;
  int height = 20;
  int **field = newField(width, height);

  ck_assert_ptr_nonnull(field);

  for (int i = 0; i < height; i++) {
    ck_assert_ptr_nonnull(field[i]);
    for (int j = 0; j < width; j++) {
      ck_assert_int_eq(field[i][j], 0);
    }
  }

  freeField(&field, height);
  ck_assert_ptr_null(field);
}
END_TEST

START_TEST(test_freeField_handles_null) {
  int **field = NULL;

  freeField(&field, 0);
  ck_assert_ptr_null(field);
}
END_TEST

START_TEST(test_newField_frees_memory_on_failure) {
  int **field = newField(-1, -1);
  ck_assert_ptr_null(field);

  field = newField(-1, 1);
  ck_assert_ptr_null(field);
}
END_TEST

START_TEST(test_freeField_releases_all_memory) {
  int **field = newField(5, 5);
  ck_assert_ptr_nonnull(field);

  freeField(&field, 5);
  ck_assert_ptr_null(field);
}
END_TEST

Suite *tetris_memory_utils_suite(void) {
  Suite *s = suite_create("Tetris Memory Utils");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_newField_creates_valid_field);
  tcase_add_test(tc_core, test_freeField_handles_null);
  tcase_add_test(tc_core, test_newField_frees_memory_on_failure);
  tcase_add_test(tc_core, test_freeField_releases_all_memory);

  suite_add_tcase(s, tc_core);
  return s;
}
