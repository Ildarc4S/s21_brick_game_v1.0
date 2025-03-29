#include <stdlib.h>
#include <time.h>

#include "./include/frontend.h"

void gameLoop() {
  Keyboard_t kb = initKeyboard();
  Window_t window = initWindow();

  while (!window.checkGameExit()) {
    redrawwin(stdscr);

    kb.listen(&kb);
    window.draw(&window);

    wnoutrefresh(stdscr);
    doupdate();
  }
}

int main() {
  initNcurses();
  srand(time(NULL));

  gameLoop();

  endwin();
}
