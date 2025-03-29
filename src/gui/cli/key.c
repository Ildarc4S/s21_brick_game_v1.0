#include "./include/key.h"

double calcDeltaTime(struct timeval current_time, struct timeval last_time) {
  return (current_time.tv_sec - last_time.tv_sec) * 1000.0 +
         (current_time.tv_usec - last_time.tv_usec) / 1000.0;
}

bool isHold(int key, double hold_timeout) {
  static struct timeval last_time = {0};
  struct timeval current_time = {0};
  gettimeofday(&current_time, NULL);

  bool is_hold = false;
  static int prev_key = ERR;

  if (prev_key != key) {
    prev_key = key;
  } else {
    is_hold = calcDeltaTime(current_time, last_time) <= hold_timeout;
  }

  last_time = current_time;
  return is_hold;
}

void _listen(Keyboard_t *this) {
  int key = getch();

  Button_t button = {.key = key, .hold = isHold(key, 1000)};
  for (int i = 0; i < KEYBOARD_COUNT; i++) {
    if (this->keyboard_listeners[i].key == button.key) {
      this->keyboard_listeners[i].listenerFunc(button);
    }
  }
}

Keyboard_t initKeyboard() {
  return (Keyboard_t){.keyboard_listeners =
                          {
                              {KEY_UP, upKeyPressed},
                              {KEY_DOWN, downKeyPressed},
                              {KEY_LEFT, leftKeyPressed},
                              {KEY_RIGHT, rightKeyPressed},
                              {' ', spaceKeyPressed},
                              {'s', startKeyPressed},
                              {'p', pauseKeyPressed},
                              {'q', exitKeyPressed},
                          },
                      .listen = _listen};
}
