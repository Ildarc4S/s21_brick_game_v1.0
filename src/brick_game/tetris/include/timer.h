/**
 * @file timer.h
 * @brief Модуль таймера для управления игровым временем
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/**
 * @def Количество миллисекунд в секунде
 */
#define TIMER_MILLISECONDS_PER_SECOND 1000

/**
 * @def Количество микросекунд в миллисекунде
 */
#define TIMER_MICROSECONDS_PER_MILLISECOND 1000

/**
 * @def Начальный интервал между тиками (мс)
 */
#define TIMER_INITIAL_TICK_INTERVAL 1000

/**
 * @struct Timer_t
 * @brief Структура таймера для управления игровым временем
 */
typedef struct _timer {
  struct timeval current_time;  ///< Текущее время
  struct timeval last_time;     ///< Время предыдущего обновления
  long tick;                    ///< Текущий интервал между тиками (мс)
  long default_tick;            ///< Интервал по умолчанию (мс)

  /**
   * @brief Обновляет текущее время
   */
  void (*updateCurrenTime)(struct _timer *timer);

  /**
   * @brief Обновляет время последнего тика
   */
  void (*updateLastTime)(struct _timer *timer);

  /**
   * @brief Вычисляет разницу во времени
   */
  long (*calcDiff)(struct _timer *timer);
} Timer_t;

/**
 * @brief Инициализирует таймер
 * @return Инициализированный объект таймера
 */
Timer_t initTimer();

#endif  // TIMER_H
