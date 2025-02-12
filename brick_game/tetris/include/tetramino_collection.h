#ifndef TETRAMINO_COLLCECTION
#define TETRAMINO_COLLCECTION

#include "./tetramino.h"

typedef struct _tetramino_collection {
  Tetramino_t *tetraminos;
  int size;

  void (*pushTetramino)(struct _tetramino_collection *, Tetramino_t);

  int (*getSize)(struct _tetramino_collection *);
  int (*setSize)(struct _tetramino_collection *, int);
  Tetramino_t *(*getRandomTetranimo)(struct _tetramino_collection *);

  void (*destructor)(struct _tetramino_collection *);
} TetraminoCollection_t;

TetraminoCollection_t *initTetraminoCollection();

#endif
