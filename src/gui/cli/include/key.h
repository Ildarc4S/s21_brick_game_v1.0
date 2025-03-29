
#ifndef KEY_H
#define KEY_H

#include <ncurses.h>
#include <stdio.h>
#include <sys/time.h>

#include "./key_configuration.h"

#define KEYBOARD_COUNT 8

typedef struct _keyboard_listener {
  int key;
  void (*listenerFunc)(Button_t);
} KeyboardListener_t;

typedef struct _keyboard {
  KeyboardListener_t keyboard_listeners[KEYBOARD_COUNT];

  void (*listen)(struct _keyboard *);
} Keyboard_t;

Keyboard_t initKeyboard();

#endif  // KEY_H
