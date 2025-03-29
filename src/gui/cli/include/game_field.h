#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <ncurses.h>

#include "./objects.h"

#define GAME_FIELD_CELL_WIDTH 2
#define GAME_FIELD_CENTER_DIVISOR 2
#define GAME_FIELD_CENTER_OFFSET 1

#define GAME_FIELD_GAME_FIELD_INIT_X 0
#define GAME_FIELD_GAME_FIELD_INIT_Y 0

typedef struct _game_field {
  int x;
  int y;

  int width;
  int height;

  void (*drawField)(struct _game_field *);
} GameField_t;

GameField_t initGameField(int width, int height);

#endif  // GAME_FIELD_H
