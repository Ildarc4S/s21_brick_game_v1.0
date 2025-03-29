#include <check.h>

#include "tests.h"

START_TEST(test_fsm_states) {
  Tetris_t *tetris = initTetris();

  tetris->state = TETRIS_STATE_EXIT;
  userInput(Down, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_EXIT);
  tetris->exit(tetris);
  tetris = NULL;
}
END_TEST

START_TEST(test_start_state) {
  Tetris_t *tetris = initTetris();
  ck_assert_int_eq(tetris->state, TETRIS_STATE_START);

  userInput(Start, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  tetris->state = TETRIS_STATE_START;
  userInput(Terminate, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_EXIT);

  tetris->state = TETRIS_STATE_START;
  userInput(Down, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_START);

  userInput(Terminate, false);
  tetris = NULL;
}
END_TEST

START_TEST(test_move_state) {
  Tetris_t *tetris = initTetris();
  tetris->start(tetris);

  tetris->state = TETRIS_STATE_MOVE;

  userInput(Pause, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_PAUSE);

  tetris->state = TETRIS_STATE_MOVE;
  userInput(Left, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  userInput(Right, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  userInput(Up, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  userInput(Action, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  userInput(Start, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  userInput(Terminate, false);
}
END_TEST

START_TEST(test_pause_state) {
  Tetris_t *tetris = initTetris();
  tetris->state = TETRIS_STATE_PAUSE;

  userInput(Terminate, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_EXIT);
  tetris->state = TETRIS_STATE_PAUSE;

  userInput(Start, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);
  tetris->state = TETRIS_STATE_PAUSE;

  userInput(Pause, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_PAUSE);

  userInput(Up, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_PAUSE);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_game_over_state) {
  Tetris_t *tetris = initTetris();
  tetris->state = TETRIS_STATE_GAME_OVER;

  userInput(Start, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  tetris->state = TETRIS_STATE_GAME_OVER;
  userInput(Up, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_GAME_OVER);

  tetris->state = TETRIS_STATE_GAME_OVER;
  userInput(Terminate, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_EXIT);
}
END_TEST

START_TEST(test_hold_actions) {
  Tetris_t *tetris = initTetris();
  tetris->start(tetris);
  tetris->state = TETRIS_STATE_MOVE;

  userInput(Down, true);
}
END_TEST

Suite *tetris_fsm_suite(void) {
  Suite *s = suite_create("Tetris FSM");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_fsm_states);
  tcase_add_test(tc_core, test_start_state);
  tcase_add_test(tc_core, test_move_state);
  tcase_add_test(tc_core, test_pause_state);
  tcase_add_test(tc_core, test_game_over_state);
  tcase_add_test(tc_core, test_hold_actions);

  suite_add_tcase(s, tc_core);
  return s;
}
