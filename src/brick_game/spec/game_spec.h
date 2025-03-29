/**
 * @file game_spec.h
 * @brief Заголовочный файл, содержащий определения и прототипы функций для игры
 * "Тетрис".
 */

#ifndef GAME_SCPEC_H
#define GAME_SCPEC_H

/**
 * @def Ширина игрового поля.
 */
#define FIELD_WIDTH 10

/**
 * @def Высота игрового поля.
 */
#define FIELD_HEIGHT 20

/**
 * @def Высота тетромино (фигуры в тетрисе).
 */
#define TETRAMINO_HEIGHT 4

/**
 * @def Ширина тетромино (фигуры в тетрисе).
 */
#define TETRAMINO_WIDTH 4

/**
 * @def Доп размер для границ поля.
 */
#define FIELD_BORDER 2

#include <stdbool.h>

/**
 * @enum UserAction_t
 * @brief Действия пользователя.
 */
typedef enum {
  Start,      ///< Начать игру.
  Pause,      ///< Поставить игру на паузу.
  Terminate,  ///< Завершить игру.
  Left,       ///< Движение влево.
  Right,      ///< Движение вправо.
  Up,         ///< Движение вверх.
  Down,       ///< Движение вниз.
  Action      ///< Действие (например, поворот фигуры).
} UserAction_t;

/**
 * @struct GameInfo_t
 * @brief Структура, содержащая информацию о текущем состоянии игры.
 */
typedef struct {
  int **field;     ///< Двумерный массив, представляющий игровое поле.
  int **next;      ///< Двумерный массив, представляющий следующую фигуру.
  int score;       ///< Текущий счет.
  int high_score;  ///< Рекордный счет.
  int level;       ///< Текущий уровень.
  int speed;       ///< Текущая скорость игры.
  int pause;       ///< Текущий статус игры (см. PauseMode)
} GameInfo_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Обрабатывает пользовательский ввод.
 * @param action Действие пользователя.
 * @param hold Флаг, указывающий, зажата ли клавиша.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Обновляет текущее состояние игры.
 * @return Структура GameInfo_t с актуальной информацией о состоянии игры.
 */
GameInfo_t updateCurrentState();

#ifdef __cplusplus
}
#endif

#endif  // GAME_SCPEC_H
