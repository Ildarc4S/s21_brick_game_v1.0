/**
 * @file tetramino_collection.h
 * @brief Модуль коллекции тетромино для игры
 */

#ifndef TETRAMINO_COLLECTION_H
#define TETRAMINO_COLLECTION_H

#include <stdlib.h>

#include "./tetramino.h"

/**
 * @def Количество различных тетромино в коллекции
 */
#define TETRAMINO_COLLCECTION_SIZE 7

/**
 * @def Начальная X-координата для новых тетромино
 */
#define TETRAMINO_COLLCECTION_INITIAL_X 0

/**
 * @def Начальная Y-координата для новых тетромино
 */
#define TETRAMINO_COLLCECTION_INITIAL_Y 0

/**
 * @struct TetraminoCollection_t
 * @brief Коллекция всех возможных тетромино в игре
 */
typedef struct _tetramino_collection {
  Tetramino_t tetraminos[TETRAMINO_COLLCECTION_SIZE];  ///< Массив тетромино
  int size;                                            ///< Размер коллекции
  Tetramino_t *(*getRandomTetranimo)(
      struct _tetramino_collection
          *);  ///< Функция получения случайного тетромино
} TetraminoCollection_t;

/**
 * @brief Инициализирует коллекцию тетромино
 * @return Инициализированная коллекция
 *
 * @note Включает все стандартные 7 видов тетромино
 */
TetraminoCollection_t initTetraminoCollection();

#endif  // TETRAMINO_COLLECTION_H
