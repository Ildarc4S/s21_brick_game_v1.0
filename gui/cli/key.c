#include "key.h"
#include <stdlib.h>
#include <ncurses.h>

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

Keyboard_t *_constructorKeyboard();
void _destructorKeyboard(Keyboard_t *kb); 

void _listen(Keyboard_t *this) {
  int key = getch();
  if (key == ERR) {
    return;
  }
  
  Button_t button = {.key = key};
  for (int i = 0; i < this->size; i++) {
    if (this->keyboard_listen_list[i].key == button.key) {
      this->keyboard_listen_list[i].listenerFunc(button);
    }
  }
}

Keyboard_t *_constructorKeyboard() {
  Keyboard_t *new_keyboard = malloc(sizeof(Keyboard_t));

  new_keyboard->constructor = _constructorKeyboard;
  new_keyboard->destructor = _destructorKeyboard;
  new_keyboard->addKeyboardListener = _addKeyboardListener;
  new_keyboard->destroyKeyboardListener = _destructorKeyboard;
  
  new_keyboard->keyboard_listen_list = NULL;
  new_keyboard->size = 0;

  new_keyboard->listen = _listen;
  return new_keyboard;
}

void _destructorKeyboard(Keyboard_t *kb) {
  kb->destroyKeyboardListener(kb);
  free(kb);
}


Keyboard_t* initKeyboard() {
  static Keyboard_t *keyboard = NULL;
  if (!keyboard) {
    keyboard = _constructorKeyboard();
  }
  return keyboard;
}


