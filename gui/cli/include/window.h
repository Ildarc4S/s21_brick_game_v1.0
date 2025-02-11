#ifndef WINDOW_H
#define WINDOW_H

#include "./../../../brick_game/tetris/include/objects.h"

typedef enum {
  PANEL_GREEN_COLOR = 7,
  PANEL_RED_COLOR,
  PANEL_YELLOW_COLOR,
  PANEL_BLUE_COLOR,
} Color_t;

typedef struct _panel {
  int x;
  int y;

  char head_text[50];
  char text[50][50];
  int size;
  int score;
  int level;

  Color_t color;

  void (*draw)(struct _panel *_this);
} Panel_t;

typedef struct _game_field {
  int x;
  int y;

  int width;
  int height;

  Tetris_t *tetris;

  void (*drawField)(struct _game_field *_this);
  void (*drawTetramino)(struct _game_field *_this);
  void (*updateTetramino)(struct _game_field *_this, Tetris_t *tetris);
} GameField_t;

typedef struct _window {
  Panel_t nextFigurePanel;
  Panel_t scorePanel;
  Panel_t levelPanel;
  Panel_t helpPanel;
  GameField_t game_field;

  void (*draw)(struct _window *_this);
} Window_t;

Window_t _constructorWindow(Tetris_t *tetris);

#endif  // WINDOW_H
