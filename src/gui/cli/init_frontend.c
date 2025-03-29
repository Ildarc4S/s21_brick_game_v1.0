#include "./include/init_frontend.h"

#include "./include/objects.h"

typedef enum {
  CUSTOM_COLOR_RED = 8,
  CUSTOM_COLOR_MAGENTA = 9,
  CUSTOM_COLOR_BLUE = 10,
  CUSTOM_COLOR_GREEN = 11,
  CUSTOM_COLOR_DARK_MAGENTA = 12,
  CUSTOM_COLOR_ORANGE = 13,
  CUSTOM_COLOR_YELLOW = 14,
} CustomColor_t;

void initColorPairs() {
  init_color(CUSTOM_COLOR_RED, 1000, 0, 0);
  init_color(CUSTOM_COLOR_MAGENTA, 1000, 0, 1000);
  init_color(CUSTOM_COLOR_BLUE, 0, 0, 1000);
  init_color(CUSTOM_COLOR_GREEN, 0, 1000, 0);
  init_color(CUSTOM_COLOR_DARK_MAGENTA, 500, 0, 500);
  init_color(CUSTOM_COLOR_ORANGE, 1000, 647, 0);
  init_color(CUSTOM_COLOR_YELLOW, 1000, 1000, 0);

  init_pair(OBJECT_CODE_TETRAMINO_I, CUSTOM_COLOR_RED, COLOR_BLACK);
  init_pair(OBJECT_CODE_TETRAMINO_O, CUSTOM_COLOR_MAGENTA, COLOR_BLACK);
  init_pair(OBJECT_CODE_TETRAMINO_T, CUSTOM_COLOR_BLUE, COLOR_BLACK);
  init_pair(OBJECT_CODE_TETRAMINO_S, CUSTOM_COLOR_GREEN, COLOR_BLACK);
  init_pair(OBJECT_CODE_TETRAMINO_Z, CUSTOM_COLOR_DARK_MAGENTA, COLOR_BLACK);
  init_pair(OBJECT_CODE_TETRAMINO_J, CUSTOM_COLOR_ORANGE, COLOR_BLACK);
  init_pair(OBJECT_CODE_TETRAMINO_L, CUSTOM_COLOR_ORANGE, COLOR_BLACK);

  init_pair(OBJECT_CODE_SNAKE, CUSTOM_COLOR_GREEN, COLOR_BLACK);
  init_pair(OBJECT_CODE_APPLE, CUSTOM_COLOR_RED, COLOR_BLACK);

  init_pair(PANEL_COLOR_YELLOW, CUSTOM_COLOR_YELLOW, COLOR_BLACK);
  init_pair(PANEL_COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(PANEL_COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(PANEL_COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
}

void initNcurses() {
  initscr();             /**< Initialize ncurses */
  cbreak();              /**< Disable line buffering */
  noecho();              /**< Disable echoing of typed characters */
  keypad(stdscr, TRUE);  /**< Enable special key input (e.g., arrow keys) */
  curs_set(0);           /**< Hide the cursor */
  nodelay(stdscr, TRUE); /**< Enable non-blocking input */
  start_color();         /**< Initialize color functionality */
  initColorPairs();      /**< Initialize color pairs for game elements */
  timeout(300);          /**< Set input timeout (in milliseconds) */
}
