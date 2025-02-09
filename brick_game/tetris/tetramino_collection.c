#include <stdlib.h>
#include "./include/tetramino_collection.h"

void initAllTetraminoCollectionBricks(TetramninoCollection_t *this) {
  Tetramino_t tetramino_i = {
    .x = 0,
    .y = 0,
    .color = COLOR_RED,
    .brick = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}
  };

  Tetramino_t tetramino_o = {
    .x = 0,
    .y = 0,
    .color = COLOR_PINK,
    .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}
  };

  Tetramino_t tetramino_t = {
    .x = 0,
    .y = 0,
    .color = COLOR_BLUE,
    .brick = {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}
  };

  Tetramino_t tetramino_s = {
    .x = 0,
    .y = 0,
    .color = COLOR_GREEN,
    .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}
  };

  Tetramino_t tetramino_z = {
    .x = 0,
    .y = 0,
    .color = COLOR_PURPLE,
    .brick = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}
  };

  Tetramino_t tetramino_j = {
    .x = 0,
    .y = 0,
    .color = COLOR_ORANGE,
    .brick = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}
  };

  Tetramino_t tetramino_l = {
    .x = 0,
    .y = 0,
    .color = COLOR_YELLOW,
    .brick = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}
  };

  this->pushTetramino(this, tetramino_i); 
  this->pushTetramino(this, tetramino_o); 
  this->pushTetramino(this, tetramino_t); 
  this->pushTetramino(this, tetramino_s); 
  this->pushTetramino(this, tetramino_z); 
  this->pushTetramino(this, tetramino_j); 
  this->pushTetramino(this, tetramino_l); 
}

int _getTetraminoCollectionSize(TetramninoCollection_t *this) {
  return this->size;
}

int _setTetraminoCollectionSize(TetramninoCollection_t *this, int size) {
  return this->size = size;
}

void _pushTetraminoToCollection(TetramninoCollection_t *this, Tetramino_t tetramino) {
  int new_size = this->getSize(this) + 1;
  this->tetraminos = realloc(this->tetraminos, sizeof(Tetramino_t)*new_size);
  if (this->tetraminos) {
    this->tetraminos[new_size] = tetramino;
    this->setSize(this, new_size);  
  }
}

void _destroyTetraminosFromCollection(TetramninoCollection_t *this) {
  if (!this) return;

  free(this->tetraminos);
  this->tetraminos = NULL;
  this->setSize(this, 0);
}

void _destructorTetraminoCollection(TetramninoCollection_t *this) {
  if (!this) return;

  _destroyTetraminosFromCollection(this);
  free(this);
}

TetramninoCollection_t *_constructorTetramino() {
  TetramninoCollection_t *collection = (TetramninoCollection_t*)malloc(sizeof(TetramninoCollection_t));

  collection->setSize = _setTetraminoCollectionSize;
  collection->getSize = _getTetraminoCollectionSize;
  collection->pushTetramino = _pushTetraminoToCollection;

  collection->constructor = _constructorTetramino;
  collection->destructor = _destructorTetraminoCollection;

  collection->setSize(collection, 0);
  collection->tetraminos = NULL;

  return collection;
}

TetramninoCollection_t *initTetraminoCollection() {
  static TetramninoCollection_t *this = NULL;

  if (!NULL) {
    this = _constructorTetramino();
    initAllTetraminoCollectionBricks(this);
  }

  return this;
}
