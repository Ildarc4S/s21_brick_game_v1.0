/**
 * @file fsm.h
 * @brief Модуль конечного автомата игры Тетрис
 */

#ifndef FSM_H
#define FSM_H

#include "./tetris.h"
#include "./utils.h"

/**
 * @brief Обновляет состояние конечного автомата
 * @param action Действие пользователя
 * @param hold Флаг удержания клавиши
 *
 * @note Вызывает соответствующий обработчик состояния
 */
void updateFSM(UserAction_t action, bool hold);

/**
 * @brief Обработчик начального состояния
 * @param tetris Указатель на объект игры
 * @param action Действие пользователя
 */
void startHandler(Tetris_t *tetris, UserAction_t action);

/**
 * @brief Обработчик состояния движения
 * @param tetris Указатель на объект игры
 * @param action Действие пользователя
 * @param hold Флаг удержания клавиши
 */
void moveHandler(Tetris_t *tetris, UserAction_t action, bool hold);

/**
 * @brief Обработчик состояния паузы
 * @param tetris Указатель на объект игры
 * @param action Действие пользователя
 */
void pauseHandler(Tetris_t *tetris, UserAction_t action);

/**
 * @brief Обработчик состояния завершения игры
 * @param tetris Указатель на объект игры
 * @param action Действие пользователя
 */
void gameOverHandler(Tetris_t *tetris, UserAction_t action);

#endif  // FSM_H
