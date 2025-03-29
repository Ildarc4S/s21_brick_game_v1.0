/**
 * @file tetramino.h
 * @brief Заголовочный файл для работы с тетромино - игровыми фигурами
 */

#ifndef TETRAMINO_H
#define TETRAMINO_H

#include "./../../spec/game_spec.h"
#include "./color.h"

/**
 * @struct Tetramino_t
 * @brief Структура, описывающая тетромино (игровую фигуру)
 *
 * Содержит информацию о положении, цвете и форме тетромино.
 */
typedef struct {
  int x;          ///< X-координата позиции тетромино на поле
  int y;          ///< Y-координата позиции тетромино на поле
  Color_t color;  ///< Цвет тетромино (из перечисления Color_t)
  int brick[TETRAMINO_HEIGHT]
           [TETRAMINO_WIDTH];  ///< Матрица 4x4, описывающая форму фигуры
} Tetramino_t;

#endif  // TETRAMINO_H
