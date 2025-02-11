#ifndef TIMER_H
#define TIMER_H
#include <sys/time.h>

typedef struct _timer {
  struct timeval current_time;
  struct timeval last_time;
  long tick;

  void (*updateCurrenTime)(struct _timer *_this);
  void (*updateLastTime)(struct _timer *_this);
  long (*calcDiff)(struct _timer *_this);

  long (*getTick)(struct _timer *_this);
  void (*setTick)(struct _timer *_this, long tick);
} Timer_t;

Timer_t *initTimer();

#endif  // TIMER_H
