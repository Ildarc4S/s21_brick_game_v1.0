#include "./include/tetris.h"

void getRealBrickSize(Tetramino_t *tetramino, int *min_x, int *max_x,
                      int *max_y) {
  *min_x = 4;
  *max_x = -1;
  *max_y = -1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetramino->brick[i][j]) {
        if (j < *min_x)
          *min_x = j;
        if (j > *max_x)
          *max_x = j;
        if (i > *max_y)
          *max_y = i;
      }
    }
  }
}

int checkCollideOtherBreak(Tetris_t *tetris, Tetramino_t *tetramino) {
  int result_code = 0;
  int x = tetramino->x;
  int y = tetramino->y;

  for (int i = 0; i < TETRAMINO_HEIGHT && !result_code; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH && !result_code; j++) {
      if (tetramino->brick[i][j]) {
        int field_x = x + j;
        int field_y = y + i;

        if (tetris->info.game_info.field[field_y][field_x]) {
          result_code = 1;
        }
      }
    }
  }
  return result_code;
}

void checkCollideSide(Tetris_t *tetris, Tetramino_t *tetramino, int min_x,
                      int max_x, int max_y, int *collide_left_x,
                      int *collide_right_x, int *collide_bottom_y) {
  if (min_x <= 0) {
    *collide_left_x = 1;
  }

  if (max_x >= FIELD_WIDTH + 1) {
    *collide_right_x = 1;
  }

  if (max_y >= FIELD_HEIGHT + 1 || checkCollideOtherBreak(tetris, tetramino)) {
    *collide_bottom_y = 1;
  }
}

void collideProcess(Tetris_t *tetris, Tetramino_t *tetramino,
                    int *collide_left_x, int *collide_right_x,
                    int *collide_bottom_y) {
  int min_x = 0;
  int max_x = 0;
  int max_y = 0;

  getRealBrickSize(tetramino, &min_x, &max_x, &max_y);

  max_x = tetramino->x + max_x;
  min_x = tetramino->x + min_x;
  max_y = tetramino->y + max_y;

  checkCollideSide(tetris, tetramino, min_x, max_x, max_y, collide_left_x,
                   collide_right_x, collide_bottom_y);
}

int isCollide(Tetris_t *tetris, Tetramino_t *tetramino) {
  int collide_left_x = 0;
  int collide_right_x = 0;
  int collide_bottom_y = 0;
  collideProcess(tetris, tetramino, &collide_left_x, &collide_right_x,
                 &collide_bottom_y);

  return collide_left_x || collide_right_x || collide_bottom_y;
}

void replaceTetramin(Tetris_t *tetris, Tetramino_t *tetramino) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      tetris->info.curr_tetramino->brick[i][j] = tetramino->brick[i][j];
    }
  }
  tetris->info.curr_tetramino->x = tetramino->x;
  tetris->info.curr_tetramino->y = tetramino->y;
}

void insertBrick(Tetris_t *tetris) {
  int x = tetris->info.curr_tetramino->x;
  int y = tetris->info.curr_tetramino->y;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      if (tetris->info.curr_tetramino->brick[i][j]) {
        tetris->info.game_info.field[y + i][x + j] =
            tetris->info.curr_tetramino->brick[i][j];
      }
    }
  }
}

void copyBrick(int brick_one[4][4], int brick_two[4][4]) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      brick_one[i][j] = brick_two[i][j];
    }
  }
}

void rotateTetramino(Tetramino_t *tetramino) {
  int temp[4][4];
  copyBrick(temp, tetramino->brick);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      temp[j][TETRAMINO_WIDTH - i - 1] = tetramino->brick[i][j];
    }
  }
  copyBrick(tetramino->brick, temp);
}

void shiftLines(Tetris_t *this, int *index) {
  for (int k = *index; k > 1; k--) {
    for (int j = 1; j <= FIELD_WIDTH; j++) {
      this->info.game_info.field[k][j] = this->info.game_info.field[k - 1][j];
    }
  }
  *index += 1;
}

void cleanLines(Tetris_t *this) {
  int erase_line_count = 0;
  for (int i = FIELD_HEIGHT; i > 0; i--) {
    int erase_line = 1;
    for (int j = 1; j < FIELD_WIDTH + 1; j++) {
      if (this->info.game_info.field[i][j] == 0) {
        erase_line = 0;
      }
    }
    if (erase_line) {
      erase_line_count++;
      shiftLines(this, &i);
    }
  }

  Score_t score = constructorScore();
  score.convertLineCountToScore(&score, erase_line_count);

  this->level.setScore(&this->level, &score);
  this->level.updateLevel(&this->level);

  this->updateScore(this);
  this->updateLevel(this);
}
