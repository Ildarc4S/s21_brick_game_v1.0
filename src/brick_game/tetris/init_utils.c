/**
 * @file init_utils.c
 * @brief Реализация функций инициализации
 */

#include "./include/init_utils.h"

/**
 * @brief Инициализирует структуру игровой информации
 */
GameInfo_t initGameInfo() {
  return (GameInfo_t){.field = newField(FIELD_WIDTH + FIELD_BORDER,
                                        FIELD_HEIGHT + FIELD_BORDER),
                      .next = newField(TETRAMINO_WIDTH, TETRAMINO_HEIGHT),
                      .score = LEVEL_MANAGER_INITIAL_SCORE,
                      .high_score = TETRIS_INITIAL_HIGH_SCORE,
                      .level = LEVEL_MANAGER_INITIAL_LEVEL,
                      .speed = TETRIS_INITIAL_SPEED,
                      .pause = PAUSE_MODE_START};
}

/**
 * @brief Инициализирует текущую тетромино
 */
Tetramino_t initCurrentTetramino() {
  return (Tetramino_t){
      .x = TETRAMINO_COLLCECTION_INITIAL_X,
      .y = TETRAMINO_COLLCECTION_INITIAL_Y,
      .color = TETRAMINO_COLOR_BLUE,
      .brick = {{0}}  // Инициализация нулями
  };
}
