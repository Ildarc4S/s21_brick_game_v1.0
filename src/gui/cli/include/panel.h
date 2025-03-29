#ifndef PANEL_H
#define PANEL_H

#include <string.h>

#include "./objects.h"

#define PANEL_SNAKE_HELP_TEXT_START 6
#define PANEL_SNAKE_HELP_TEXT_COUNT 6

#define PANEL_TETRIS_HELP_TEXT_START 0
#define PANEL_TETRIS_HELP_TEXT_COUNT 6

#define PANEL_CELL_WIDTH 2

#define PANEL_TEXT_SIZE 50
#define PANEL_TEXT_LINE_COUNT 12
#define PANEL_TEXT_LINE_COUNT_ZERO 0

typedef struct _panel {
  int x;
  int y;

  char head_text[PANEL_TEXT_SIZE];
  char text[PANEL_TEXT_LINE_COUNT][PANEL_TEXT_SIZE];
  int size;

  PanelMode_t mode;
  PanelColor_t color;

  void (*draw)(struct _panel *);
} Panel_t;

Panel_t initPanel(int x, int y, const char *title, const char **text, int size,
                  PanelColor_t color, PanelMode_t mode);

#endif  // PANEL_H
