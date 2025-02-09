#include "../../brick_game/tetris/include/backend.h"
#include "include/frontend.h"
#include <unistd.h>

void sigcat() {

}

void gameLoop() {
  Tetris_t *t = createTetris();
  fillField(t->info.game_info.field);
  createBrick(t);
  int a  = 0;
  t->info.curr_tetramino->x = 5;
  t->info.curr_tetramino->y = 20;
  while (true) {
    timeout(300); 
    clear();
      t->action(t, 0);
    a++;
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
