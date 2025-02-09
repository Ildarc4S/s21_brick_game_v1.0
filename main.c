#include "brick_game/tetris/include/backend.h"
#include "gui/cli/include/frontend.h"
#include <unistd.h>
#include "gui/cli/button.h"
#include "gui/cli/key.h"

void upKeyPressed(Button btn) {
  userInput(Up, btn.hold);
}

void leftKeyPressed(Button btn) {
  userInput(Left, btn.hold);
}

void rightKeyPressed(Button btn) {
  userInput(Right, btn.hold);
}

void downKeyPressed(Button btn) {
  userInput(Down, btn.hold);
}

void spaceKeyPressed(Button btn) {
  userInput(Action, btn.hold);
}

void startKeyPressed(Button btn) {
  userInput(Start, btn.hold);
}

void pauseKeyPressed(Button btn) {
  userInput(Pause, btn.hold);
}

void exitKeyPressed(Button btn) {
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
  keyboard->addKeyboardListener(keyboard, KEY_EXIT, exitKeyPressed);
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
