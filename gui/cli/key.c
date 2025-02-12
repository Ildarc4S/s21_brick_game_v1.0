#include "./include/key.h"
#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>

void _addKeyboardListener(Keyboard_t *kb, int key, void (*listenerFunc)(Button_t btn)) {
  kb->keyboard_listen_list = realloc(kb->keyboard_listen_list, sizeof(KeyboardListener_t)*(kb->size + 1)); 
  kb->size++; 
  KeyboardListener_t new_keyboard_listener = {
    .key = key, 
    .listenerFunc = listenerFunc
  };

  kb->keyboard_listen_list[kb->size-1] =  new_keyboard_listener;
}

void _destroyKeyboardListener(Keyboard_t *kb) {
  if (!kb) return;

  if (kb->keyboard_listen_list) {
    free(kb->keyboard_listen_list);
    kb->keyboard_listen_list = NULL;
    kb->size = 0;
  }
}

void _destructorKeyboard(Keyboard_t *kb) {
  kb->destroyKeyboardListener(kb);
  free(kb);
}

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
    is_hold = calcDeltaTime(current_time ,last_time) <= hold_timeout;
  }

  last_time = current_time;
  return is_hold;
}

void _listen(Keyboard_t *this) {
  int key = getch();
  
  Button_t button = {.key = key, .hold = isHold(key, 1000)};
  for (int i = 0; i < this->size; i++) {
    if (this->keyboard_listen_list[i].key == button.key) {
      this->keyboard_listen_list[i].listenerFunc(button);
    }
  }
}

Keyboard_t *constructorKeyboard() {
  Keyboard_t *new_keyboard = malloc(sizeof(Keyboard_t));

  new_keyboard->destructor = _destructorKeyboard;
  new_keyboard->addKeyboardListener = _addKeyboardListener;
  new_keyboard->destroyKeyboardListener = _destroyKeyboardListener;
  new_keyboard->listen = _listen;

  new_keyboard->keyboard_listen_list = NULL;
  new_keyboard->size = 0;

  return new_keyboard;
}

Keyboard_t* initKeyboard() {
  static Keyboard_t *keyboard = NULL;
  if (!keyboard) {
    keyboard = constructorKeyboard();
  }
  return keyboard;
}

