#ifndef TETRAMINO_COLLCECTION
#define TETRAMINO_COLLCECTION

#include "./tetramino.h"

typedef struct _tetramino_collection {
  Tetramino_t *tetraminos;
  int size;

  void (*pushTetramino)(struct _tetramino_collection *_this,
                        Tetramino_t tetramino);

  int (*getSize)(struct _tetramino_collection *_this);
  int (*setSize)(struct _tetramino_collection *_this, int size);
  Tetramino_t *(*getRandomTetranimo)(struct _tetramino_collection *_this);

  struct _tetramino_collection *(*constructor)();
  void (*destructor)(struct _tetramino_collection *_this);
} TetraminoCollection_t;

TetraminoCollection_t *initTetraminoCollection();

#endif
