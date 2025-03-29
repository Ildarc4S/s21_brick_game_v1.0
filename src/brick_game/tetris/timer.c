/**
 * @file timer.c
 * @brief Реализация таймера для игры
 */

#include "./include/timer.h"

/**
 * @brief Обновляет текущее время в таймере
 * @param self Указатель на объект таймера
 *
 * @details Использует системный вызов gettimeofday()
 */
void _updateCurrentTime(Timer_t *self) {
  struct timeval time = {0};
  gettimeofday(&time, NULL);
  self->current_time = time;
}

/**
 * @brief Обновляет время последнего тика
 * @param self Указатель на объект таймера
 *
 * @note Копирует текущее время в last_time
 */
void _updateLastTime(Timer_t *self) { self->last_time = self->current_time; }

/**
 * @brief Вычисляет разницу между текущим и предыдущим временем
 * @param self Указатель на объект таймера
 * @return Разница во времени в миллисекундах
 *
 * @details Алгоритм:
 * 1. Обновляет текущее время
 * 2. Вычисляет разницу в секундах и микросекундах
 * 3. Конвертирует в миллисекунды
 */
long _calcTimeDiff(Timer_t *self) {
  self->updateCurrenTime(self);
  return (self->current_time.tv_sec - self->last_time.tv_sec) *
             TIMER_MILLISECONDS_PER_SECOND +
         (self->current_time.tv_usec - self->last_time.tv_usec) /
             TIMER_MICROSECONDS_PER_MILLISECOND;
}

/**
 * @brief Инициализирует таймер
 * @return Инициализированный объект таймера
 *
 * @details Устанавливает:
 * - Начальные значения времени
 * - Интервал по умолчанию
 * - Указатели на функции работы с временем
 */
Timer_t initTimer() {
  struct timeval time = {0};
  gettimeofday(&time, NULL);

  return (Timer_t){
      .current_time = time,
      .last_time = time,
      .tick = TIMER_INITIAL_TICK_INTERVAL,
      .updateCurrenTime = _updateCurrentTime,
      .updateLastTime = _updateLastTime,
      .calcDiff = _calcTimeDiff,
  };
}
