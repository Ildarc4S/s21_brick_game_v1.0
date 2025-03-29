/**
 * @file tetris_state.h
 * @brief Определение состояний игры Тетрис
 */

#ifndef TETRIS_STATE_H
#define TETRIS_STATE_H

/**
 * @enum TetrisState_t
 * @brief Перечисление возможных состояний игры
 *
 * Описывает все возможные состояния, в которых может находиться игра Тетрис
 * в процессе своего жизненного цикла.
 */
typedef enum {
  TETRIS_STATE_START,      ///< Начальное состояние (заставка/меню)
  TETRIS_STATE_SPAWN,      ///< Состояние появления новой фигуры
  TETRIS_STATE_MOVE,       ///< Состояние движения/управления фигурой
  TETRIS_STATE_PAUSE,      ///< Игра на паузе
  TETRIS_STATE_GAME_OVER,  ///< Конец игры (проигрыш)
  TETRIS_STATE_EXIT,       ///< Выход из игры
  TETRIS_STATE_ATTACH      ///< Фигура прикрепилась к полю
} TetrisState_t;

#endif  // TETRIS_STATE_H
