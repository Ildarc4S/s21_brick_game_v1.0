#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

typedef struct _score {
  int score;

  int (*getScore)(struct _score *);
  void (*setScore)(struct _score *, int);
  void (*convertLineCountToScore)(struct _score *, int);
} Score_t;

typedef struct _level {
  Score_t score;
  int level;
  int max_level_score;

  int (*getLevel)(struct _level *);
  void (*setLevel)(struct _level *, int);
  void (*setScore)(struct _level *, Score_t *);
  void (*updateLevel)(struct _level *);
} Level_t;

Level_t constructorLevel();
Score_t constructorScore();

#endif // LEVEL_MANAGER_H
