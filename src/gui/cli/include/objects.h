#ifndef OBJECTS_CODE_H
#define OBJECTS_CODE_H

#include <ncurses.h>

#include "./../../../brick_game/spec/game_spec.h"

typedef enum {
  OBJECT_CODE_AIR = -2,
  OBJECT_CODE_WALL = -1,

  OBJECT_CODE_TETRAMINO_I = 1,
  OBJECT_CODE_TETRAMINO_O = 2,
  OBJECT_CODE_TETRAMINO_T = 3,
  OBJECT_CODE_TETRAMINO_S = 4,
  OBJECT_CODE_TETRAMINO_Z = 5,
  OBJECT_CODE_TETRAMINO_J = 6,
  OBJECT_CODE_TETRAMINO_L = 7,

  OBJECT_CODE_SNAKE = 10,
  OBJECT_CODE_APPLE = 11
} ObjectCode_t;

typedef enum {
  PAUSE_MODE_PAUSE = 1,
  PAUSE_MODE_GAME_CONTINUE = 2,
  PAUSE_MODE_START = 3,
  PAUSE_MODE_GAME_OVER = 4,
  PAUSE_MODE_EXIT = 5
} PauseMode_t;

typedef enum {
  PANEL_COLOR_GREEN = 21,  /**< Green color for the panel */
  PANEL_COLOR_RED = 22,    /**< Red color for the panel */
  PANEL_COLOR_YELLOW = 23, /**< Yellow color for the panel */
  PANEL_COLOR_BLUE = 24,   /**< Blue color for the panel */
} PanelColor_t;

typedef enum {
  PANEL_MODE_TEXT = -3,
  PANEL_MODE_HIGH_SCORE = -4,
  PANEL_MODE_SPEED = -5,
  PANEL_MODE_LEVEL = -6,
  PANEL_MODE_CUR_SCORE = -7,
  PANEL_MODE_NEXT_FIGURE = -8
} PanelMode_t;

#endif  // OBJECTS_CODE_H
