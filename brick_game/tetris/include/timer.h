#ifndef TIMER_H
#define TIMER_H
#include <sys/time.h>

typedef struct _timer {
  struct timeval current_time;
  struct timeval last_time;
  long tick;

  void (*updateCurrenTime)(struct _timer *);
  void (*updateLastTime)(struct _timer *);
  long (*calcDiff)(struct _timer *);

  long (*getTick)(struct _timer *);
  void (*setTick)(struct _timer *, long);
} Timer_t;

Timer_t constructorTimer();

#endif // TIMER_H
