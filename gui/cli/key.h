#ifndef KEY_H
#define KEY_H

#include "./button.h"

typedef struct _keyboard_listener {
  int key;
  void (*listenerFunc)(Button_t btn);
} KeyboardListener_t;

typedef struct _keyboard {
  KeyboardListener_t *keyboard_listen_list;
  int size;

  void (*listen)(struct _keyboard *btn);
  void (*addKeyboardListener)(struct _keyboard *kb, int key,
                            void (*listenerFunc)(Button_t btn));
  void (*destroyKeyboardListener)(struct _keyboard *kb);

  struct _keyboard *(*constructor)();
  void (*destructor)(struct _keyboard *kb);
} Keyboard_t;

Keyboard_t* initKeyboard();

#endif  // KEY_H
