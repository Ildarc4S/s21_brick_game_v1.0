#include "brick_game/tetris/include/backend.h"
#include "gui/cli/include/frontend.h"
#include "gui/cli/include/window.h"

#include <unistd.h>
#include "gui/cli/include/key.h"
#include <stdlib.h>
#include <time.h>

void upKeyPressed(Button_t btn) {
  userInput(Up, btn.hold);
}

void leftKeyPressed(Button_t btn) {
  userInput(Left, btn.hold);
}

void rightKeyPressed(Button_t btn) {
  userInput(Right, btn.hold);
}

void downKeyPressed(Button_t btn) {
  userInput(Down, btn.hold);
}

void spaceKeyPressed(Button_t btn) {
  userInput(Action, btn.hold);
}

void startKeyPressed(Button_t btn) {
  userInput(Start, btn.hold);
}

void pauseKeyPressed(Button_t btn) {
  userInput(Pause, btn.hold);
}

void exitKeyPressed(Button_t btn) {
  userInput(Terminate, btn.hold);
}

void initKeyboardHandlers() {
  Keyboard_t *keyboard = initKeyboard();
  keyboard->addKeyboardListener(keyboard, KEY_UP, upKeyPressed);
  keyboard->addKeyboardListener(keyboard, KEY_DOWN, downKeyPressed);
  keyboard->addKeyboardListener(keyboard, KEY_LEFT, leftKeyPressed);
  keyboard->addKeyboardListener(keyboard, KEY_RIGHT, rightKeyPressed);
  keyboard->addKeyboardListener(keyboard, ' ', spaceKeyPressed);
  keyboard->addKeyboardListener(keyboard, 's', startKeyPressed);
  keyboard->addKeyboardListener(keyboard, 'p', pauseKeyPressed);
  keyboard->addKeyboardListener(keyboard, 'q', exitKeyPressed);
}

void gameLoop() {
  Tetris_t *tetris = initTetris();
  Keyboard_t *kb = initKeyboard();
  initKeyboardHandlers();
  Window_t window = _constructorWindow(tetris);

  timeout(300);
  while (tetris->state != EXIT) {
    redrawwin(stdscr); // Перерисовываем без очистки экрана
                       
    kb->listen(kb);      
    window.draw(&window);

    wnoutrefresh(stdscr); // Подготавливаем изменения
    doupdate();           // Выводим их одним кадром
  }
}

int main() {
 initNcurses();
 srand(time(NULL));
 gameLoop();
 endwin();
}
