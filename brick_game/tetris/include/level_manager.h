#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

typedef struct _score {
  int score;

  int (*getScore)(struct _score *_this);
  void (*setScore)(struct _score *_this, int score);
  void (*convertLineCountToScore)(struct _score *_this, int line_count);
} Score_t;

typedef struct _level {
  Score_t score;
  int level;
  int max_level_score;

  int (*getLevel)(struct _level *_this);
  void (*setLevel)(struct _level *_this, int level);
  void (*setScore)(struct _level *_this, Score_t *score);
  void (*updateLevel)(struct _level *_this);
} Level_t;

Level_t constructorLevel();
Score_t constructorScore();

#endif  // LEVEL_MANAGER_H
