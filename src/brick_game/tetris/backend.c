#include "./include/fsm.h"
#include "./include/tetris.h"

/**
 * @brief Обрабатывает пользовательский ввод и передает его в FSM
 *
 * @details Функция является оберткой для updateFSM(), передающей
 * пользовательский ввод в конечный автомат игры. Вызывается при любом действии
 * игрока.
 *
 * @see updateFSM()
 * @see UserAction_t
 *
 * @code
 * // Пример использования
 * userInput(Right, false);  // Одиночное нажатие вправо
 * @endcode
 */
void userInput(UserAction_t action, bool hold) { updateFSM(action, hold); }

/**
 * @brief Обновляет текущее состояние игры и возвращает актуальную информацию
 * @return Структура GameInfo_t с текущим состоянием игры
 *
 * @details Функция выполняет:
 * 1. Инициализацию/получение объекта игры
 * 2. Обновление игрового состояния
 * 3. Возврат актуальной информации о состоянии игры
 *
 * @warning Возвращаемая структура содержит указатели на динамическую память,
 * которая должна быть освобождена при завершении работы
 *
 * @see Tetris_t
 * @see GameInfo_t
 *
 * @code
 * // Пример использования
 * GameInfo_t info = updateCurrentState();
 * // Использование информации...
 * @endcode
 */
GameInfo_t updateCurrentState() {
  Tetris_t *tetris = initTetris();
  tetris->updateTetrisState(tetris);
  return tetris->game_info;
}
