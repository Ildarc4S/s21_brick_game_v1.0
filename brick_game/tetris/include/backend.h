#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  START,
  SPAWN,
  MOVE,
  SHIFT,
  PAUSE,
  GAME_OVER,
  EXIT,
  ATTACH
} TetrisState_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#endif  // BACKEND_H
