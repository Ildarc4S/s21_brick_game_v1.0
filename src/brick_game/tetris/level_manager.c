/**
 * @file level_manager.c
 * @brief Реализация управления уровнем и счетом
 */

#include "./include/level_manager.h"

/**
 * @brief Конвертирует количество собранных линий в очки
 * @param self Указатель на объект счета
 * @param line_count Количество собранных линий (1-4)
 *
 * @details Использует предустановленную таблицу конвертации
 * @warning Не проверяет выход за границы массива (line_count должен быть 1-4)
 */
void _convertLineCountToScore(Score_t *self, int line_count) {
  self->score += self->score_converter[line_count - 1];
}

/**
 * @brief Обновляет уровень сложности на основе набранных очков
 * @param self Указатель на объект уровня
 *
 * @note Уровень рассчитывается как (очки / max_level_score) + 1
 * @warning Не превышает установленный максимальный уровень
 */
void _updateLevel(Level_t *self) {
  self->level = self->score.score / self->max_level_score + 1;
  if (self->level > self->max_level) {
    self->level = self->max_level;
  }
}

/**
 * @brief Инициализирует систему подсчета очков
 * @return Инициализированный объект Score_t
 *
 * @details Устанавливает:
 * - Начальный счет = 0
 * - Таблицу конвертации линий в очки
 * - Функцию обработки
 */
Score_t initScore() {
  return (Score_t){
      .score = LEVEL_MANAGER_INITIAL_SCORE,
      .score_converter = {LEVEL_MANAGER_SCORE_FOR_ONE_LINE,
                          LEVEL_MANAGER_SCORE_FOR_TWO_LINES,
                          LEVEL_MANAGER_SCORE_FOR_THREE_LINES,
                          LEVEL_MANAGER_SCORE_FOR_FOUR_LINES},
      .convertLineCountToScore = _convertLineCountToScore,
  };
}

/**
 * @brief Инициализирует систему уровней
 * @return Инициализированный объект Level_t
 *
 * @details Устанавливает:
 * - Начальный уровень = 1
 * - Максимальный уровень = 10
 * - Очков для перехода = 600
 * - Функцию обновления уровня
 */
Level_t initLevel() {
  return (Level_t){.score = initScore(),
                   .level = LEVEL_MANAGER_INITIAL_LEVEL,
                   .max_level_score = LEVEL_MANAGER_MAX_LEVEL_SCORE,
                   .max_level = LEVEL_MANAGER_MAX_LEVEL,
                   .updateLevel = _updateLevel};
}
