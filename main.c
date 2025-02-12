#include <time.h>

#include "./gui/cli/include/key_configuration.h"
#include "./gui/cli/include/window.h"
#include "gui/cli/include/key.h"

void gameLoop() {
  Tetris_t *tetris = initTetris();
  Keyboard_t *kb = initKeyboard();
  Window_t window = _constructorWindow(tetris);

  initKeyboardConfiguration();
  while (tetris->state != EXIT) {
    redrawwin(stdscr); // Перерисовываем без очистки экрана

    kb->listen(kb);
    window.draw(&window);

    wnoutrefresh(stdscr); // Подготавливаем изменения
    doupdate();           // Выводим их одним кадром
  }

  tetris->destructor(tetris);
  kb->destructor(kb);
}

int main() {
  initNcurses();
  srand(time(NULL));
  gameLoop();
  endwin();
}
