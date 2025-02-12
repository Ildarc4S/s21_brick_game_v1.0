#include "tests.h"
#include <check.h>
#include "./../brick_game/tetris/include/tetris.h"
#include "./../brick_game/tetris/include/tetris.h"

START_TEST(test_start_state) {
    Tetris_t *tetris = initTetris();
    ck_assert_int_eq(tetris->state, START);

    userInput(Terminate, false);
    ck_assert_int_eq(tetris->state, EXIT);
    tetris->state = START;

    userInput(Start, false);
    ck_assert_int_eq(tetris->state, MOVE);

    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_move_state) {
    Tetris_t *tetris = initTetris();
    tetris->start(tetris);

    tetris->state = MOVE; 
    userInput(Terminate, false);
    ck_assert_int_eq(tetris->state, EXIT);
    tetris->state = MOVE; 

    userInput(Pause, false);
    ck_assert_int_eq(tetris->state, PAUSE);
    
    tetris->state = MOVE;
    userInput(Left, false);
    ck_assert_int_eq(tetris->state, MOVE);

    userInput(Right, false);
    ck_assert_int_eq(tetris->state, MOVE);

    userInput(Up, false);
    ck_assert_int_eq(tetris->state, MOVE);

    userInput(Down, false);
    ck_assert_int_eq(tetris->state, MOVE);

    userInput(Action, false);
    ck_assert_int_eq(tetris->state, MOVE);

    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_pause_state) {
    Tetris_t *tetris = initTetris();
    tetris->state = PAUSE; 

    userInput(Terminate, false);
    ck_assert_int_eq(tetris->state, EXIT);
    tetris->state = PAUSE; 

    userInput(Start, false);
    ck_assert_int_eq(tetris->state, MOVE);
    tetris->state = PAUSE; 

    userInput(Pause, false);
    ck_assert_int_eq(tetris->state, PAUSE);

    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_game_over_state) {
    Tetris_t *tetris = initTetris();
    tetris->state = GAME_OVER; 

    userInput(Start, false);
    ck_assert_int_eq(tetris->state, MOVE);

    tetris->state = GAME_OVER; 
    userInput(Terminate, false);
    ck_assert_int_eq(tetris->state, EXIT);

    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_hold_actions) {
    Tetris_t *tetris = initTetris();
    tetris->start(tetris);
    tetris->state = MOVE; 

    userInput(Down, true);

    tetris->destructor(tetris);
}
END_TEST

Suite* tetris_fsm_suite(void) {
    Suite* s = suite_create("Tetris FSM");

    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_start_state);
    tcase_add_test(tc_core, test_move_state);
    tcase_add_test(tc_core, test_pause_state);
    tcase_add_test(tc_core, test_game_over_state);
    tcase_add_test(tc_core, test_hold_actions);

    suite_add_tcase(s, tc_core);
    return s;
}
