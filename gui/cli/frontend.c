#include "./include/frontend.h"
#include "./include/color.h"

void initNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  nodelay(stdscr, TRUE);
  start_color();
  initColorPairs();
  timeout(300);
}

void initColorPairs() {
  init_pair(TETRAMINO_COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_MAGNETA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

  init_pair(PANEL_COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(PANEL_COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(PANEL_COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(PANEL_COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
}
