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

Timer_t *constructorTimer() {
  Timer_t *timer = malloc(sizeof(Timer_t));
  if (timer != NULL) {
    struct timeval time = {0};
    gettimeofday(&time, NULL);
    
    timer->current_time = time;
    timer->last_time = time;

    timer->updateCurrenTime = _updateCurrentTime;
    timer->updateLastTime = _updateLastTime;
    timer->calcDiff = _calcTimeDiff;

    timer->getTick = _getTimerTick;
    timer->setTick = _setTimerTick;

    timer->tick = 1500;
  }
  return timer;
}

Timer_t *initTimer() {
  static Timer_t *timer = NULL;
  if (!timer) {
    timer = constructorTimer();    
  }
  return timer;
}



