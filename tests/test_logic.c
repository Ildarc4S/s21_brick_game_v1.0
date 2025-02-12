#include "tests.h"
#include "./../brick_game/tetris/include/tetris.h"
#include "./../brick_game/tetris/include/tetris_utils.h"

#include <check.h>
#include <unistd.h>

START_TEST(test_tetris_initialization) {
    Tetris_t* tetris = initTetris();
    
    ck_assert_ptr_nonnull(tetris);
    ck_assert_int_eq(tetris->state, START);
    ck_assert_ptr_nonnull(tetris->info.game_info.field);
    ck_assert_ptr_nonnull(tetris->info.game_info.next);
    ck_assert_int_eq(tetris->info.game_info.pause, 2);
    ck_assert_int_eq(tetris->info.game_info.level, 1);
    ck_assert_int_eq(tetris->info.game_info.score, 0);
    ck_assert_ptr_null(tetris->info.curr_tetramino);
    ck_assert_ptr_null(tetris->info.next_tetramino);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_tetris_update_state) {
    Tetris_t* tetris = initTetris();
    
    tetris->start(tetris);
    tetris->state = MOVE;
    int tetramino_y = tetris->info.curr_tetramino->y; 
    sleep(1);
    GameInfo_t update_one = updateCurrentState();

    ck_assert_int_eq(tetramino_y + 1, tetris->info.curr_tetramino->y); 

    tetris->state = ATTACH;
    int score = tetris->info.game_info.score;
    GameInfo_t update_two = updateCurrentState();
    
    ck_assert_int_eq(score, tetris->info.game_info.score);

    tetris->destructor(tetris);
}
END_TEST


START_TEST(test_spawn_and_collision_detection) {
    Tetris_t* tetris = initTetris();
    tetris->spawn(tetris);
    
    ck_assert_ptr_nonnull(tetris->info.curr_tetramino);
    ck_assert_ptr_nonnull(tetris->info.next_tetramino);
    ck_assert_int_eq(tetris->state, MOVE);

    // Force collision by filling spawn area
    for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
        for (int j = 0; j < TETRAMINO_WIDTH; j++) {
            tetris->info.game_info.field[1 + i][(FIELD_WIDTH/2) + j] = 1;
        }
    }
    
    tetris->spawn(tetris);
    ck_assert_int_eq(tetris->state, GAME_OVER);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_movement_and_collision) {
    Tetris_t* tetris = initTetris();
    tetris->start(tetris);
    
    // Test left movement
    int initial_x = tetris->info.curr_tetramino->x;
    tetris->left(tetris, false);
    ck_assert_int_eq(tetris->info.curr_tetramino->x, initial_x - 1);
    
    // Test right movement
    initial_x = tetris->info.curr_tetramino->x;
    tetris->right(tetris, false);
    ck_assert_int_eq(tetris->info.curr_tetramino->x, initial_x + 1);

    // Test down movement
    int initial_y = tetris->info.curr_tetramino->y;
    tetris->down(tetris, false);
    ck_assert_int_eq(tetris->info.curr_tetramino->y, initial_y + 1);

    while(!isCollide(tetris, tetris->info.curr_tetramino)) {
        tetris->info.curr_tetramino->y++;
    }
    tetris->down(tetris, true);
    ck_assert_int_eq(tetris->state, ATTACH);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_rotation_logic) {
    Tetris_t* tetris = initTetris();
    tetris->start(tetris);
    
    tetris->info.curr_tetramino = &tetris->collection->tetraminos[tetris->collection->size-1];
    tetris->info.curr_tetramino->y = 5;
    int original_brick[4][4];
    copyBrick(original_brick, tetris->info.curr_tetramino->brick);
    
    tetris->action(tetris, false);
    ck_assert(memcmp(original_brick, tetris->info.curr_tetramino->brick, sizeof(original_brick)) != 0);
    
    Tetramino_t temp = *tetris->info.curr_tetramino;
    while(!isCollide(tetris, &temp)) {
        temp.x++;
    }
    replaceTetramin(tetris, &temp);
    tetris->action(tetris, false);
    ck_assert(memcmp(temp.brick, tetris->info.curr_tetramino->brick, sizeof(temp.brick)) == 0);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_line_clearing_and_scoring) {
    Tetris_t* tetris = initTetris();
    
    // Fill a complete line
    for (int j = 1; j <= FIELD_WIDTH; j++) {
        tetris->info.game_info.field[FIELD_HEIGHT][j] = 1;
    }
    
    int initial_score = tetris->info.game_info.score;
    cleanLines(tetris);
    ck_assert_int_gt(tetris->info.game_info.score, initial_score);
    
    // Check line clearing
    int empty = 1;
    for (int j = 1; j <= FIELD_WIDTH; j++) {
        if (tetris->info.game_info.field[FIELD_HEIGHT][j] != 0) {
            empty = 0;
            break;
        }
    }
    ck_assert_int_eq(empty, 1);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_game_state_transitions) {
    Tetris_t* tetris = initTetris();
    
    // Start -> Move
    tetris->start(tetris);
    ck_assert_int_eq(tetris->state, MOVE);
    
    // Move -> Pause
    tetris->pause(tetris);
    ck_assert_int_eq(tetris->state, PAUSE);
    
    // Pause -> Move
    tetris->start(tetris);
    ck_assert_int_eq(tetris->state, MOVE);
    
    // Move -> Game Over
    while(tetris->state != GAME_OVER) {
        tetris->down(tetris, true);
        if(tetris->state == ATTACH) {
            tetris->spawn(tetris);
        }
    }
    ck_assert_int_eq(tetris->state, GAME_OVER);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

START_TEST(test_level_progression) {
    Tetris_t* tetris = initTetris();
    tetris->start(tetris);
    
    // Simulate score gain
    tetris->level.score.score = 1500;
    tetris->level.updateLevel(&tetris->level);
    tetris->updateLevel(tetris);
    ck_assert_int_eq(tetris->info.game_info.level, 3);
    
    // Check timer adjustment
    ck_assert_int_lt(tetris->timer.tick, 1000);

    tetris->exit(tetris);
    tetris->destructor(tetris);
}
END_TEST

Suite* tetris_suite(void) {
    Suite* s = suite_create("Tetris Logic");
    TCase* tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_tetris_initialization);
    tcase_add_test(tc_core, test_tetris_update_state);
    tcase_add_test(tc_core, test_spawn_and_collision_detection);
    tcase_add_test(tc_core, test_movement_and_collision);
    tcase_add_test(tc_core, test_rotation_logic);
    tcase_add_test(tc_core, test_line_clearing_and_scoring);
    tcase_add_test(tc_core, test_game_state_transitions);
    tcase_add_test(tc_core, test_level_progression);
    
    suite_add_tcase(s, tc_core);
    return s;
}

