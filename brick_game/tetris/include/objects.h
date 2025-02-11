#ifndef OBJECTS_H
#define OBJECTS_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

#define TETRAMINO_WIDTH 4
#define TETRAMINO_HEIGHT 4

#include <stdbool.h>
#include "./tetramino_collection.h"
#include "./timer.h"
#include "./level_manager.h"

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

typedef struct {
  GameInfo_t game_info;
  Tetramino_t *curr_tetramino;
  Tetramino_t *next_tetramino;
} TetrisInfo_t;

typedef struct _tetris {
  TetrisState_t state;
  TetrisInfo_t info;

  TetraminoCollection_t *collection;
  Timer_t *timer;
  Level_t level;

  void (*start)(struct _tetris* tetris);
  void (*spawn)(struct _tetris* tetris);
  void (*left)(struct _tetris* tetris, bool hold);
  void (*action)(struct _tetris* tetris, bool hold);
  void (*right)(struct _tetris* tetris, bool hold);
  void (*up)(struct _tetris* tetris, bool hold);
  void (*down)(struct _tetris* tetris, bool hold);
  void (*pause)(struct _tetris* tetris);
  void (*gameOver)(struct _tetris* tetris);
  void (*exit)(struct _tetris* tetris);

  void (*updateScore)(struct _tetris *_this);
  void (*updateLevel)(struct _tetris *_this);
} Tetris_t;

void userInput(UserAction_t action, int hold);

GameInfo_t updateCurrentState();

#endif  // OBJECTS_H
