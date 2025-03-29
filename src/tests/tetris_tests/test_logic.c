#include <check.h>
#include <unistd.h>

#include "tests.h"

START_TEST(test_tetris_initialization) {
  Tetris_t* tetris = initTetris();

  ck_assert_ptr_nonnull(tetris);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_START);
  ck_assert_ptr_nonnull(tetris->game_info.field);
  ck_assert_ptr_nonnull(tetris->game_info.next);
  ck_assert_int_eq(tetris->game_info.pause, PAUSE_MODE_START);
  ck_assert_int_eq(tetris->game_info.level, 1);
  ck_assert_int_eq(tetris->game_info.score, 0);
  ck_assert_ptr_null(tetris->next_tetramino);

  tetris->exit(tetris);
}
START_TEST(test_tetris_update_state) {
  Tetris_t* tetris = initTetris();

  tetris->start(tetris);
  tetris->state = TETRIS_STATE_MOVE;
  int tetramino_y = tetris->curr_tetramino.y;
  sleep(1);
  GameInfo_t game_info = updateCurrentState();

  ck_assert_int_eq(tetramino_y + 1, tetris->curr_tetramino.y);

  tetris->state = TETRIS_STATE_ATTACH;
  int score = tetris->game_info.score;
  game_info = updateCurrentState();
  (void)game_info;

  ck_assert_int_eq(score, tetris->game_info.score);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_spawn_and_collision_detection) {
  Tetris_t* tetris = initTetris();
  tetris->spawn(tetris);

  ck_assert_ptr_nonnull(tetris->next_tetramino);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      tetris->game_info.field[1 + i][(FIELD_WIDTH / 2) + j] = OBJECT_CODE_WALL;
    }
  }

  tetris->spawn(tetris);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_GAME_OVER);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_movement_and_collision) {
  Tetris_t* tetris = initTetris();
  tetris->start(tetris);

  int initial_x = tetris->curr_tetramino.x;

  tetris->left(tetris, false);
  ck_assert_int_eq(tetris->curr_tetramino.x, initial_x - 1);

  tetris->right(tetris, false);
  ck_assert_int_eq(tetris->curr_tetramino.x, initial_x);

  tetris->down(tetris, false);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_ATTACH);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_right_movement_at_right_boundary) {
  Tetris_t* tetris = initTetris();
  tetris->start(tetris);

  tetris->curr_tetramino = tetris->collection.tetraminos[0];
  tetris->curr_tetramino.x = FIELD_WIDTH - TETRAMINO_WIDTH + 2;
  int initial_x = tetris->curr_tetramino.x;

  tetris->right(tetris, false);

  ck_assert_int_eq(tetris->curr_tetramino.x, initial_x);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_left_movement_at_left_boundary) {
  Tetris_t* tetris = initTetris();
  tetris->start(tetris);

  tetris->curr_tetramino = tetris->collection.tetraminos[0];
  tetris->curr_tetramino.x = 0;
  int initial_x = tetris->curr_tetramino.x;

  tetris->left(tetris, false);

  ck_assert_int_eq(tetris->curr_tetramino.x, initial_x);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_rotation_logic) {
  Tetris_t* tetris = initTetris();
  tetris->start(tetris);

  tetris->curr_tetramino =
      tetris->collection.tetraminos[tetris->collection.size - 1];
  tetris->curr_tetramino.y = 5;
  int original_brick[TETRAMINO_HEIGHT][TETRAMINO_WIDTH];
  copyTetramino(original_brick, tetris->curr_tetramino.brick);

  tetris->action(tetris, false);
  ck_assert(memcmp(original_brick, tetris->curr_tetramino.brick,
                   sizeof(original_brick)) != 0);

  Tetramino_t temp = tetris->curr_tetramino;
  while (!isCollide(tetris, &temp)) {
    temp.x++;
  }
  replaceTetramino(tetris, &temp);
  tetris->action(tetris, false);
  ck_assert(memcmp(temp.brick, tetris->curr_tetramino.brick,
                   sizeof(temp.brick)) == 0);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_line_clearing_and_scoring) {
  Tetris_t* tetris = initTetris();

  for (int j = 1; j <= FIELD_WIDTH; j++) {
    tetris->game_info.field[FIELD_HEIGHT][j] = OBJECT_CODE_WALL;
  }

  int initial_score = tetris->game_info.score;
  clearLines(tetris);
  ck_assert_int_gt(tetris->game_info.score, initial_score);

  int empty = 1;
  for (int j = 1; j <= FIELD_WIDTH && empty; j++) {
    if (tetris->game_info.field[FIELD_HEIGHT][j] != OBJECT_CODE_AIR) {
      empty = 0;
    }
  }
  ck_assert_int_eq(empty, 1);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_game_state_transitions) {
  Tetris_t* tetris = initTetris();

  tetris->start(tetris);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  tetris->pause(tetris);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_PAUSE);

  tetris->start(tetris);
  ck_assert_int_eq(tetris->state, TETRIS_STATE_MOVE);

  while (tetris->state != TETRIS_STATE_GAME_OVER) {
    tetris->down(tetris, true);
    if (tetris->state == TETRIS_STATE_ATTACH) {
      tetris->spawn(tetris);
    }
  }
  ck_assert_int_eq(tetris->state, TETRIS_STATE_GAME_OVER);

  tetris->exit(tetris);
}
END_TEST

START_TEST(test_level_progression) {
  Tetris_t* tetris = initTetris();
  tetris->start(tetris);

  tetris->level.score.score = 1500;
  tetris->level.updateLevel(&tetris->level);
  tetris->updateLevel(tetris);
  ck_assert_int_eq(tetris->game_info.level, 3);
  ck_assert_int_lt(tetris->timer.tick, 1000);

  tetris->exit(tetris);
}
END_TEST

Suite* tetris_suite(void) {
  Suite* s = suite_create("Tetris Logic");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_tetris_initialization);
  tcase_add_test(tc_core, test_tetris_update_state);
  tcase_add_test(tc_core, test_spawn_and_collision_detection);
  tcase_add_test(tc_core, test_right_movement_at_right_boundary);
  tcase_add_test(tc_core, test_left_movement_at_left_boundary);
  tcase_add_test(tc_core, test_movement_and_collision);
  tcase_add_test(tc_core, test_rotation_logic);
  tcase_add_test(tc_core, test_line_clearing_and_scoring);
  tcase_add_test(tc_core, test_game_state_transitions);
  tcase_add_test(tc_core, test_level_progression);

  suite_add_tcase(s, tc_core);
  return s;
}
