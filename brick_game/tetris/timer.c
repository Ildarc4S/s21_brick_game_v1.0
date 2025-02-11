#include "./include/timer.h"
#include <stdlib.h>

void _updateCurrentTime(Timer_t *this) {
  struct timeval time = {0};
  gettimeofday(&time, NULL);
  this->current_time = time;
}

void _updateLastTime(Timer_t *this) {
  this->last_time = this->current_time;
}

long _calcTimeDiff(Timer_t *this) {
   this->updateCurrenTime(this);
   return (this->current_time.tv_sec - this->last_time.tv_sec) * 1000 +
          (this->last_time.tv_usec - this->last_time.tv_usec) / 1000;
}

long _getTimerTick(Timer_t *this) {
  return this->tick;
}

void _setTimerTick(Timer_t *this, long tick) {
  this->tick = tick; 
}

Timer_t constructorTimer() {
  struct timeval time = {0};
  gettimeofday(&time, NULL);
    
  return (Timer_t) {
    .current_time = time,
    .last_time = time,

    .updateCurrenTime = _updateCurrentTime,
    .updateLastTime = _updateLastTime,
    .calcDiff = _calcTimeDiff,

    .getTick = _getTimerTick,
    .setTick = _setTimerTick,

    .tick = 1000
  };
}




