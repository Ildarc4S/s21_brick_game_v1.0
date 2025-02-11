#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdlib.h>

#include "./data_base.h"
#include "./level_manager.h"
#include "./tetramino_collection.h"
#include "./tetris_info.h"
#include "./timer.h"
#include "./utils.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef struct _tetris {
  TetrisState_t state;
  TetrisInfo_t info;

  TetraminoCollection_t *collection;
  Timer_t timer;
  Level_t level;
  DataBase_t db;

  void (*start)(struct _tetris *);
  void (*spawn)(struct _tetris *);
  void (*left)(struct _tetris *, bool);
  void (*action)(struct _tetris *, bool);
  void (*right)(struct _tetris *, bool);
  void (*up)(struct _tetris *, bool);
  void (*down)(struct _tetris *, bool);
  void (*pause)(struct _tetris *);
  void (*gameOver)(struct _tetris *);
  void (*exit)(struct _tetris *);

  void (*updateScore)(struct _tetris *);
  void (*updateLevel)(struct _tetris *);
  void (*destructor)(struct _tetris *);
} Tetris_t;

Tetris_t *initTetris();

#endif
