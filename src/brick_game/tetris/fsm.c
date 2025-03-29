/**
 * @file fsm.c
 * @brief Реализация конечного автомата игры Тетрис
 */

#include "./include/fsm.h"

#include <ncurses.h>

/**
 * @brief Основная функция обновления конечного автомата
 */
void updateFSM(UserAction_t action, bool hold) {
  Tetris_t *tetris = initTetris();
  clearTetraminoFromField(tetris);

  switch (tetris->state) {
    case TETRIS_STATE_START:
      startHandler(tetris, action);
      break;
    case TETRIS_STATE_MOVE:
      moveHandler(tetris, action, hold);
      break;
    case TETRIS_STATE_PAUSE:
      pauseHandler(tetris, action);
      break;
    case TETRIS_STATE_GAME_OVER:
      gameOverHandler(tetris, action);
      break;
    default:
      break;
  };
}

/**
 * @brief Обрабатывает действия в начальном состоянии
 *
 * @details Доступные действия:
 * - Terminate: выход из игры
 * - Start: начало игры
 */
void startHandler(Tetris_t *tetris, UserAction_t action) {
  switch (action) {
    case Terminate:
      tetris->exit(tetris);
      break;
    case Start:
      tetris->start(tetris);
      break;
    default:
      break;
  };
}

/**
 * @brief Обрабатывает действия в состоянии движения
 *
 * @details Доступные действия:
 * - Terminate: выход из игры
 * - Pause: пауза игры
 * - Left/Right: движение по горизонтали
 * - Up: поворот фигуры
 * - Down: ускоренное падение
 * - Action: дополнительное действие
 */
void moveHandler(Tetris_t *tetris, UserAction_t action, bool hold) {
  switch (action) {
    case Terminate:
      tetris->exit(tetris);
      break;
    case Pause:
      tetris->pause(tetris);
      break;
    case Left:
      tetris->left(tetris, hold);
      break;
    case Right:
      tetris->right(tetris, hold);
      break;
    case Up:
      tetris->up(tetris, hold);
      break;
    case Down:
      tetris->down(tetris, hold);
      break;
    case Action:
      tetris->action(tetris, hold);
      break;
    default:
      break;
  };
}

/**
 * @brief Обрабатывает действия в состоянии паузы
 *
 * @details Доступные действия:
 * - Terminate: выход из игры
 * - Start: продолжение игры
 * - Pause: снятие с паузы
 */
void pauseHandler(Tetris_t *tetris, UserAction_t action) {
  switch (action) {
    case Terminate:
      tetris->exit(tetris);
      break;
    case Start:
      tetris->start(tetris);
      break;
    case Pause:
      tetris->pause(tetris);
      break;
    default:
      break;
  };
}

/**
 * @brief Обрабатывает действия в состоянии завершения игры
 *
 * @details Доступные действия:
 * - Start: новая игра
 * - Terminate: выход из игры
 */
void gameOverHandler(Tetris_t *tetris, UserAction_t action) {
  switch (action) {
    case Start:
      tetris->start(tetris);
      break;
    case Terminate:
      tetris->exit(tetris);
      break;
    default:
      break;
  };
}
