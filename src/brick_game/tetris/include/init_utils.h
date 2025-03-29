/**
 * @file init_utils.h
 * @brief Модуль инициализации игровых структур
 */

#ifndef INIT_UTILS_H
#define INIT_UTILS_H

#include "./memory_utils.h"
#include "./tetris.h"

/**
 * @brief Инициализирует структуру игровой информации
 * @return Инициализированная структура GameInfo_t
 *
 * @details Создает:
 * - Игровое поле с границами
 * - Поле для следующей фигуры
 * - Устанавливает начальные значения:
 *   - Счет и рекорд
 *   - Уровень и скорость
 *   - Статус паузы
 */
GameInfo_t initGameInfo();

/**
 * @brief Инициализирует текущую тетромино
 * @return Инициализированная структура Tetramino_t
 *
 * @details Устанавливает:
 * - Стартовые координаты
 * - Синий цвет по умолчанию
 * - Пустую матрицу фигуры
 */
Tetramino_t initCurrentTetramino();

#endif  // INIT_UTILS_H
