#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>

#include "./game_field.h"
#include "./objects.h"
#include "./panel.h"

#define WINDOW_TEXT_LINE_COUNT PANEL_TEXT_LINE_COUNT
#define WINDOW_TEXT_LINE_COUNT_ZERO PANEL_TEXT_LINE_COUNT_ZERO

#define WINDOW_FIELD_BORDER FIELD_BORDER

#define WINDOW_PANEL_COLUMN_ONE_X 15
#define WINDOW_PANEL_COLUMN_TWO_X 20
#define WINDOW_PANEL_ROW_ONE_Y 8
#define WINDOW_PANEL_ROW_TWO_Y 12
#define WINDOW_PANEL_HELP_Y 16
#define WINDOW_PANEL_NEXT_FIGURE_Y 1

typedef struct _window {
  Panel_t next_figure_panel;
  Panel_t score_panel;
  Panel_t high_score_panel;
  Panel_t level_panel;
  Panel_t help_panel;
  Panel_t speed_panel;
  GameField_t game_field;

  void (*draw)(struct _window *);
  bool (*checkGameExit)(void);
} Window_t;

Window_t initWindow();

#endif  // WINDOW_H
