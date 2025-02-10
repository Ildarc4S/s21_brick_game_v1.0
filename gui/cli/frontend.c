#include "include/frontend.h"

void initNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  nodelay(stdscr, TRUE);
  start_color();
  initColorPairs();
}

void initColorPairs() {
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_YELLOW, COLOR_BLACK);
}

void printField(GameInfo_t *game) {
  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
      if (game->field[i][j]) {
        mvprintw(i, 2 * j, "[]");
      } else {
        mvprintw(i, 2 * j, "  ");
      }
    }
  }
}

void printTetramino(Tetramino_t *tetramino) {
  if (!tetramino) return;
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetramino->brick[i][j]) {
        mvprintw(tetramino->y + i, (tetramino->x + j) * 2, "[]");
      }
    }
  }
}
