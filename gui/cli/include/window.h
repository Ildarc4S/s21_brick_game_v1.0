#ifndef WINDOW_H
#define WINDOW_H

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

typedef struct _window {
  Panel_t nextFigurePanel;
  Panel_t scorePanel;
  Panel_t levelPanel;
  Panel_t helpPanel;

  void (*draw)(struct _window *_this);
} Window_t;

Window_t _constructorWindow();

#endif  // WINDOW_H
