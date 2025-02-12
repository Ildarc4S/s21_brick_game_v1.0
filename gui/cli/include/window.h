#ifndef WINDOW_H
#define WINDOW_H

#include "./../../../brick_game/tetris/include/tetris.h"
#include "./color.h"
#include "./frontend.h"

typedef struct _panel {
  int x;
  int y;

  char head_text[50];
  char text[50][50];
  int size;
  int value;
  int mode;

  Color_t color;

  void (*draw)(struct _panel *_this);
} Panel_t;

typedef struct _game_field {
  int x;
  int y;

  int width;
  int height;

  Tetris_t *tetris;

  void (*drawField)(struct _game_field *);
  void (*drawTetramino)(struct _game_field *);
  void (*updateTetramino)(struct _game_field *, Tetris_t *);
} GameField_t;

typedef struct _window {
  Panel_t nextFigurePanel;
  Panel_t scorePanel;
  Panel_t high_score_panel;
  Panel_t levelPanel;
  Panel_t helpPanel;
  Panel_t speed_panel;
  GameField_t game_field;

  void (*draw)(struct _window *);
} Window_t;

Window_t _constructorWindow(Tetris_t *tetris);

#endif // WINDOW_H
