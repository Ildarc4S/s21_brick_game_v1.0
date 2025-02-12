#include "./include/tetramino_collection.h"
#include <stdlib.h>

void initAllTetraminoCollectionBricks(TetraminoCollection_t *this) {
  Tetramino_t tetramino_i = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_RED,
      .brick = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_o = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_BLUE,
      .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_t = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_GREEN,
      .brick = {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_s = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_YELLOW,
      .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_z = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_MAGNETA,
      .brick = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_j = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_MAGNETA,
      .brick = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_l = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_CYAN,
      .brick = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  this->pushTetramino(this, tetramino_i);
  this->pushTetramino(this, tetramino_o);
  this->pushTetramino(this, tetramino_t);
  this->pushTetramino(this, tetramino_s);
  this->pushTetramino(this, tetramino_z);
  this->pushTetramino(this, tetramino_j);
  this->pushTetramino(this, tetramino_l);
}

int _getTetraminoCollectionSize(TetraminoCollection_t *this) {
  return this->size;
}

int _setTetraminoCollectionSize(TetraminoCollection_t *this, int size) {
  return this->size = size;
}

Tetramino_t *_getRandomTetramino(TetraminoCollection_t *this) {
  int rand_index = rand() % this->getSize(this);
  return &this->tetraminos[rand_index];
}

void _pushTetraminoToCollection(TetraminoCollection_t *this,
                                Tetramino_t tetramino) {
  int new_size = _getTetraminoCollectionSize(this) + 1;
  this->tetraminos = realloc(this->tetraminos, sizeof(Tetramino_t) * new_size);
  if (this->tetraminos) {
    this->tetraminos[new_size - 1] = tetramino;
    this->size = new_size;
  }
}

void _destroyTetraminosFromCollection(TetraminoCollection_t *this) {
  if (!this) {
    return;
  }

  free(this->tetraminos);
  this->tetraminos = NULL;
  this->setSize(this, 0);
}

void _destructorTetraminoCollection(TetraminoCollection_t *this) {
  if (!this) {
    return;
  }

  _destroyTetraminosFromCollection(this);
  free(this);
}

TetraminoCollection_t *_constructorTetramino() {
  TetraminoCollection_t *collection =
      (TetraminoCollection_t *)malloc(sizeof(TetraminoCollection_t));

  collection->setSize = _setTetraminoCollectionSize;
  collection->getSize = _getTetraminoCollectionSize;
  collection->getRandomTetranimo = _getRandomTetramino;
  collection->pushTetramino = _pushTetraminoToCollection;

  collection->destructor = _destructorTetraminoCollection;

  collection->setSize(collection, 0);
  collection->tetraminos = NULL;

  return collection;
}

TetraminoCollection_t *initTetraminoCollection() {
  static TetraminoCollection_t *this = NULL;

  if (!this) {
    this = _constructorTetramino();
    initAllTetraminoCollectionBricks(this);
  }

  return this;
}
