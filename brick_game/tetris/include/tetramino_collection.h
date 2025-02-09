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

  struct _tetramino_collection *(*constructor)();
  void (*destructor)(struct _tetramino_collection *_this);
} TetramninoCollection_t;

TetramninoCollection_t *initTetraminoCollection();

#endif
