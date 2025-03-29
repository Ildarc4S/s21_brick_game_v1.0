/**
 * @file color.h
 * @brief Заголовочный файл с определениями цветов для тетромино
 */

#ifndef COLOR_H
#define COLOR_H

#include "./objects_code.h"

/**
 * @enum Color_t
 * @brief Цвета для различных типов тетромино
 *
 * Определяет цветовую схему для каждого типа тетромино, используя
 * соответствие с кодами объектов из ObjectCode_t.
 * Цвета используются для графического отображения фигур.
 */
typedef enum {
  TETRAMINO_COLOR_RED =
      OBJECT_CODE_TETRAMINO_I,  ///< Красный цвет для I-образного тетромино
  TETRAMINO_COLOR_MAGNETA =
      OBJECT_CODE_TETRAMINO_O,  ///< Пурпурный цвет для O-образного тетромино
  TETRAMINO_COLOR_BLUE =
      OBJECT_CODE_TETRAMINO_T,  ///< Синий цвет для T-образного тетромино
  TETRAMINO_COLOR_GREEN =
      OBJECT_CODE_TETRAMINO_S,  ///< Зеленый цвет для S-образного тетромино
  TETRAMINO_COLOR_DARK_MAGNETA =
      OBJECT_CODE_TETRAMINO_Z,  ///< Темно-пурпурный для Z-образного тетромино
  TETRAMINO_COLOR_DARK_YELLOW =
      OBJECT_CODE_TETRAMINO_J,  ///< Темно-желтый для J-образного тетромино
  TETRAMINO_COLOR_YELLOW =
      OBJECT_CODE_TETRAMINO_L,  ///< Желтый цвет для L-образного тетромино
} Color_t;

#endif  // COLOR_H
