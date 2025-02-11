#ifndef KEY_H
#define KEY_H

#include "./button.h"

typedef struct _keyboard_listener {
  int key;
  void (*listenerFunc)(Button_t);
} KeyboardListener_t;

typedef struct _keyboard {
  KeyboardListener_t *keyboard_listen_list;
  int size;

  void (*listen)(struct _keyboard *);
  void (*addKeyboardListener)(struct _keyboard *, int , void (*listenerFunc)(Button_t));
  void (*destroyKeyboardListener)(struct _keyboard *);

  void (*destructor)(struct _keyboard *);
} Keyboard_t;

Keyboard_t* initKeyboard();

#endif  // KEY_H
