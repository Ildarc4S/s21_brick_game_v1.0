/**
 * @file level_manager.h
 * @brief Модуль управления уровнем сложности и подсчета очков
 */

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

/**
 * @def Размер массива конвертации линий в очки
 */
#define LEVEL_MANAGER_SCORE_CONVERTER_SIZE 4

/**
 * @def Начальное количество очков
 */
#define LEVEL_MANAGER_INITIAL_SCORE 0

/**
 * @def Очки за 1 собранную линию
 */
#define LEVEL_MANAGER_SCORE_FOR_ONE_LINE 100

/**
 * @def Очки за 2 собранные линии
 */
#define LEVEL_MANAGER_SCORE_FOR_TWO_LINES 300

/**
 * @def Очки за 3 собранные линии
 */
#define LEVEL_MANAGER_SCORE_FOR_THREE_LINES 700

/**
 * @def Очки за 4 собранные линии (Tetris)
 */
#define LEVEL_MANAGER_SCORE_FOR_FOUR_LINES 1500

/**
 * @def Начальный уровень сложности
 */
#define LEVEL_MANAGER_INITIAL_LEVEL 1

/**
 * @def Необходимое количество очков для перехода на следующий уровень
 */
#define LEVEL_MANAGER_MAX_LEVEL_SCORE 600

/**
 * @def Максимально возможный уровень сложности
 */
#define LEVEL_MANAGER_MAX_LEVEL 10

/**
 * @struct Score_t
 * @brief Структура для управления счетом игрока
 */
typedef struct _score {
  int score;  ///< Текущее количество очков
  int score_converter[LEVEL_MANAGER_SCORE_CONVERTER_SIZE];  ///< Таблица
                                                            ///< конвертации
                                                            ///< линий в очки
  void (*convertLineCountToScore)(struct _score *,
                                  int);  ///< Функция добавления очков
} Score_t;

/**
 * @struct Level_t
 * @brief Структура для управления уровнем сложности
 */
typedef struct _level {
  Score_t score;        ///< Объект счета игрока
  int level;            ///< Текущий уровень сложности
  int max_level_score;  ///< Очков для перехода на след. уровень
  int max_level;        ///< Максимальный уровень
  void (*updateLevel)(struct _level *);  ///< Функция обновления уровня
} Level_t;

/**
 * @brief Инициализирует систему уровней
 * @return Инициализированный объект Level_t
 */
Level_t initLevel();

/**
 * @brief Инициализирует систему подсчета очков
 * @return Инициализированный объект Score_t
 */
Score_t initScore();

#endif  // LEVEL_MANAGER_H
