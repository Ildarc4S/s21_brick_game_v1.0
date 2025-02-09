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
  while (true) {
    timeout(300); // Устанавливаем таймаут
    clear();
    if (a % 2 == 0) {
      t->right(t, 0);
      t->down(t, 0);
    } else {
      t->left(t, 0);
    }
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
