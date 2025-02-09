#include "../../brick_game/tetris/include/backend.h"
#include "include/frontend.h"
#include <unistd.h>

void sigcat() {

}

void gameLoop() {
  Tetris_t *t = createTetris();
  fillField(t->info.game_info.field);
  t->info.game_info.field[10][5] = 1;
  createBrick(t);
  int a  = 0;
  t->info.curr_tetramino->x = 5;
  while (true) {
    timeout(300); 
    clear();
    t->down(t, 1);
    printField(&t->info.game_info);
    printTetramino(t->info.curr_tetramino);
    refresh();
    sleep(1);
  }
}

int main() {
 initNcurses();
  gameLoop();
  endwin();
}
