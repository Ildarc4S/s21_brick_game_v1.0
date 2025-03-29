/**
 * @file tetris.h
 * @brief Основной заголовочный файл игры Тетрис
 *
 * Содержит определение главной структуры игры и всех необходимых параметров.
 */

#ifndef TETRIS_H
#define TETRIS_H

#include "./../../spec/game_spec.h"
#include "./data_base.h"
#include "./level_manager.h"
#include "./tetramino_collection.h"
#include "./tetris_state.h"
#include "./timer.h"

/**
 * @def X-координата появления новых тетромино (центр поля)
 */
#define TETRIS_TETRAMINO_SPAWN_X (FIELD_WIDTH / 2)

/**
 * @def Y-координата появления новых тетромино (над полем)
 */
#define TETRIS_TETRAMINO_SPAWN_Y -1

/**
 * @def Направление движения вправо
 */
#define TETRIS_TETRAMINO_RIGHT_DIRECTION 1

/**
 * @def Направление движения влево
 */
#define TETRIS_TETRAMINO_LEFT_DIRECTION -1

/**
 * @def Начальная скорость падения фигур
 */
#define TETRIS_INITIAL_SPEED 10

/**
 * @def Начальное значение рекорда
 */
#define TETRIS_INITIAL_HIGH_SCORE 0

/**
 * @def Шаг уменьшения интервала между падениями (в мс)
 */
#define TETRIS_TICK_DECREMENT 70

/**
 * @def Шаг увеличения скорости игры
 */
#define TETRIS_SPEED_INCREMENT 10

/**
 * @struct Tetris_t
 * @brief Главная структура игры Тетрис
 *
 * Содержит все состояние игры, управляющие функции и компоненты.
 */
typedef struct _tetris {
  TetrisState_t state;               ///< Текущее состояние игры
  GameInfo_t game_info;              ///< Информация о текущей игре
  Tetramino_t curr_tetramino;        ///< Текущая падающая фигура
  Tetramino_t *next_tetramino;       ///< Следующая фигура (превью)
  TetraminoCollection_t collection;  ///< Коллекция всех возможных фигур

  Timer_t timer;   ///< Таймер для управления скоростью
  Level_t level;   ///< Уровень сложности
  DataBase_t db;   ///< База данных для хранения рекордов
  int speed_diff;  ///< Разница скорости
  long tick_diff;  ///< Разница во времени между падениями

  // Указатели на функции управления игрой
  void (*start)(struct _tetris *);         ///< Начать/продолжить игру
  void (*spawn)(struct _tetris *);         ///< Создать новую фигуру
  void (*action)(struct _tetris *, bool);  ///< Действие (поворот)
  void (*left)(struct _tetris *, bool);    ///< Движение влево
  void (*right)(struct _tetris *, bool);   ///< Движение вправо
  void (*up)(struct _tetris *, bool);      ///< Движение вверх
  void (*down)(struct _tetris *, bool);    ///< Движение вниз
  void (*pause)(struct _tetris *);         ///< Пауза игры
  void (*exit)(struct _tetris *);          ///< Выход из игры
  void (*restoreInfo)(struct _tetris *);   ///< Сброс состояния игры

  // Функции обновления состояния
  void (*updateScore)(struct _tetris *);        ///< Обновление счета
  void (*updateLevel)(struct _tetris *);        ///< Обновление уровня
  void (*updateTetrisState)(struct _tetris *);  ///< Обновление состояния игры
} Tetris_t;

/**
 * @brief Инициализирует и возвращает объект игры Тетрис
 * @return Указатель на созданный объект игры
 *
 * @note Использует статическую переменную для хранения состояния
 */
Tetris_t *initTetris();

#endif  // TETRIS_H
