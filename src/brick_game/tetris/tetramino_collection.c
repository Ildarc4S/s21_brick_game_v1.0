/**
 * @file tetramino_collection.c
 * @brief Реализация коллекции тетромино
 */

#include "./include/tetramino_collection.h"

#include <stdlib.h>

/**
 * @brief Инициализирует все тетромино в коллекции
 * @param self Указатель на коллекцию
 *
 * @details Создает и настраивает все 7 классических тетромино:
 * - I (палка)
 * - O (квадрат)
 * - T (T-образное)
 * - S (зигзаг)
 * - Z (обратный зигзаг)
 * - J (Г-образное)
 * - L (обратное Г-образное)
 *
 * Каждому тетромино присваивается уникальный цвет.
 */
void initAllTetraminoCollectionBricks(TetraminoCollection_t *self) {
  // I-тетромино (красный)
  Tetramino_t tetramino_i = {
      .color = TETRAMINO_COLOR_RED,
      .brick = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  // O-тетромино (пурпурный)
  Tetramino_t tetramino_o = {
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_MAGNETA,
      .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

  // T-тетромино (синий)
  Tetramino_t tetramino_t = {
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_BLUE,
      .brick = {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  // S-тетромино (зеленый)
  Tetramino_t tetramino_s = {
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_GREEN,
      .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}};

  // Z-тетромино (темно-пурпурный)
  Tetramino_t tetramino_z = {
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_DARK_MAGNETA,
      .brick = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

  // J-тетромино (темно-желтый)
  Tetramino_t tetramino_j = {
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_DARK_YELLOW,
      .brick = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  // L-тетромино (желтый)
  Tetramino_t tetramino_l = {
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_YELLOW,
      .brick = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  // Заполнение коллекции
  self->tetraminos[0] = tetramino_i;
  self->tetraminos[1] = tetramino_o;
  self->tetraminos[2] = tetramino_t;
  self->tetraminos[3] = tetramino_s;
  self->tetraminos[4] = tetramino_z;
  self->tetraminos[5] = tetramino_j;
  self->tetraminos[6] = tetramino_l;
}

/**
 * @brief Возвращает случайное тетромино из коллекции
 * @param self Указатель на коллекцию
 * @return Указатель на случайное тетромино
 *
 * @note Использует стандартную функцию rand()
 * @warning Требуется предварительная инициализация генератора случайных чисел
 */
Tetramino_t *_getRandomTetramino(TetraminoCollection_t *self) {
  int rand_index = rand() % self->size;
  return &self->tetraminos[rand_index];
}

/**
 * @brief Инициализирует коллекцию тетромино
 * @return Инициализированная коллекция
 *
 * @details Выполняет:
 * 1. Установку размера коллекции
 * 2. Назначение функции получения случайного тетромино
 * 3. Инициализацию всех тетромино
 */
TetraminoCollection_t initTetraminoCollection() {
  TetraminoCollection_t collection = {
      .size = TETRAMINO_COLLCECTION_SIZE,
      .getRandomTetranimo = _getRandomTetramino};

  initAllTetraminoCollectionBricks(&collection);
  return collection;
}
