#ifndef OBJECTS_H
#define OBJECTS_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

#define TETRAMINO_WIDTH 4
#define TETRAMINO_HEIGHT 4

#include <stdbool.h>
#include "./tetramino_collection.h"

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
  EXIT
} TetrisState_t;

typedef struct {
  GameInfo_t game_info;
  Tetramino_t *curr_tetramino;
  Tetramino_t *next_tetramino;
} TetrisInfo_t;

typedef struct _tetris_t {
  TetrisState_t state;
  TetrisInfo_t info;
  void (*start)(struct _tetris_t* tetris);
  void (*spawn)(struct _tetris_t* tetris);
  void (*left)(struct _tetris_t* tetris, bool hold);
  void (*action)(struct _tetris_t* tetris, bool hold);
  void (*right)(struct _tetris_t* tetris, bool hold);
  void (*up)(struct _tetris_t* tetris, bool hold);
  void (*down)(struct _tetris_t* tetris, bool hold);
  void (*pause)(struct _tetris_t* tetris);
  void (*gameOver)(struct _tetris_t* tetris);
  void (*exit)(struct _tetris_t* tetris);
} Tetris_t;

void userInput(UserAction_t action, int hold);

GameInfo_t updateCurrentState();

#endif // OBJECTS_H
