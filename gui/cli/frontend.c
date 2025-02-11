#include "include/frontend.h"
#include "include/window.h"

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
  init_pair(TETRAMINO_COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_MAGNETA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(TETRAMINO_COLOR_BLUE, COLOR_BLUE, COLOR_BLACK); 

  init_pair(PANEL_YELLOW_COLOR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(PANEL_GREEN_COLOR, COLOR_GREEN, COLOR_BLACK);
  init_pair(PANEL_RED_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(PANEL_BLUE_COLOR, COLOR_BLUE, COLOR_BLACK); 
}

void printScore() {
  GameInfo_t game = updateCurrentState();
  mvprintw(15, 40,"Score: %d", game.score);
}

void printField() {
  GameInfo_t game = updateCurrentState();
  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
      if (game.field[i][j]) {
        mvprintw(i, 2 * j, "[]");
      } else {
        mvprintw(i, 2 * j, "  ");
      }
    }
  }
  printScore();
}

void printTetramino(Tetramino_t *tetramino) {
  if (!tetramino) return;
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetramino->brick[i][j]) {
        attron(COLOR_PAIR(tetramino->color));
        mvprintw(tetramino->y + i, (tetramino->x + j) * 2, "[]");
        attroff(COLOR_PAIR(tetramino->color));
      }
    }
  }
}


