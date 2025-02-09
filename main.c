#include "brick_game/tetris/include/backend.h"
#include "gui/cli/include/frontend.h"
#include <unistd.h>
#include "gui/cli/button.h"
#include "gui/cli/key.h"
#include <stdlib.h>
#include <time.h>

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
  Tetris_t *tetris = initTetris();
  fillField(tetris->info.game_info.field);

  tetris->info.curr_tetramino = tetris->collection->getRandomTetranimo(tetris->collection);
  tetris->info.curr_tetramino->x = 5;

  timeout(500); 
  while (true) {
    clear();
    tetris->down(tetris, 1);
    printField(&tetris->info.game_info);
    printTetramino(tetris->info.curr_tetramino);
    refresh();
    sleep(1);
  }
}

int main() {
 initNcurses();
 srand(time(NULL));
  gameLoop();
  endwin();
}
