/**
 * @file tetris.c
 * @brief Реализация основных функций игры Тетрис
 */

#include "./include/tetris.h"

#include "./include/init_utils.h"
#include "./include/memory_utils.h"
#include "./include/utils.h"

/**
 * @brief Восстанавливает начальное состояние игры
 * @param self Указатель на объект игры
 */
void _restoreInfo(Tetris_t *self) {
  clearField(self->game_info.field);

  self->timer.tick = TIMER_INITIAL_TICK_INTERVAL;
  self->level.level = LEVEL_MANAGER_INITIAL_LEVEL;
  self->level.score.score = LEVEL_MANAGER_INITIAL_SCORE;

  self->game_info.level = LEVEL_MANAGER_INITIAL_LEVEL;
  self->game_info.score = LEVEL_MANAGER_INITIAL_SCORE;
  self->game_info.speed = TETRIS_INITIAL_SPEED;
}

/**
 * @brief Обработчик начала/продолжения игры
 * @param self Указатель на объект игры
 */
void _startGame(Tetris_t *self) {
  if (self->state == TETRIS_STATE_START) {
    self->spawn(self);
    self->game_info.high_score = self->db.read(&self->db);
  } else if (self->state == TETRIS_STATE_PAUSE) {
    self->state = TETRIS_STATE_MOVE;
  } else if (self->state == TETRIS_STATE_GAME_OVER) {
    self->restoreInfo(self);
    self->spawn(self);
  }
  self->game_info.pause = PAUSE_MODE_CONTINUE;
}

/**
 * @brief Создает новую фигуру на поле
 * @param self Указатель на объект игры
 */
void _spawn(Tetris_t *self) {
  if (!self) return;

  if (!self->next_tetramino) {
    self->next_tetramino =
        self->collection.getRandomTetranimo(&self->collection);
  }

  setCurrTetramino(self);
  updateNextTetraminoPreview(self);
  self->state = TETRIS_STATE_MOVE;
  checkGameOver(self);
}

/**
 * @brief Движение фигуры влево
 * @param self Указатель на объект игры
 * @param hold Флаг удержания клавиши
 */
void _left(Tetris_t *self, bool hold) {
  if (!self) return;
  (void)hold;
  moveHorizontal(self, TETRIS_TETRAMINO_LEFT_DIRECTION);
}

/**
 * @brief Движение фигуры вправо
 * @param self Указатель на объект игры
 * @param hold Флаг удержания клавиши
 */
void _right(Tetris_t *self, bool hold) {
  if (!self) return;
  (void)hold;
  moveHorizontal(self, TETRIS_TETRAMINO_RIGHT_DIRECTION);
}

/**
 * @brief Вращение фигуры
 * @param self Указатель на объект игры
 * @param hold Флаг удержания клавиши
 */
void _up(Tetris_t *self, bool hold) {
  if (!self) return;
  (void)hold;
  // Реализация вращения в функции action
}

/**
 * @brief Ускоренное падение фигуры
 * @param self Указатель на объект игры
 * @param hold Флаг удержания клавиши
 */
void _down(Tetris_t *self, bool hold) {
  if (!self) return;

  Tetramino_t *tetramino = &self->curr_tetramino;
  bool is_collide = false;

  if (hold) {
    tetramino->y++;
    if (isCollide(self, tetramino)) {
      is_collide = true;
      tetramino->y--;
    }
  } else {
    while (!isCollide(self, tetramino)) {
      tetramino->y++;
    }
    tetramino->y--;
    is_collide = true;
  }

  replaceTetramino(self, tetramino);

  if (is_collide) {
    self->state = TETRIS_STATE_ATTACH;
    insertTetraminoToField(self);
  }
}

/**
 * @brief Поворот фигуры
 * @param tetris Указатель на объект игры
 * @param hold Флаг удержания клавиши
 */
void _action(Tetris_t *tetris, bool hold) {
  if (!tetris) return;
  (void)hold;

  Tetramino_t *tetramino = &tetris->curr_tetramino;
  int temp_tetramino[TETRAMINO_HEIGHT][TETRAMINO_WIDTH];
  copyTetramino(temp_tetramino, tetramino->brick);
  rotateTetramino(tetramino);

  if (isCollide(tetris, tetramino)) {
    copyTetramino(tetramino->brick, temp_tetramino);
  }
}

/**
 * @brief Обновляет счет в игровой информации
 * @param self Указатель на объект игры
 */
void _updateTetrisScore(Tetris_t *self) {
  self->game_info.score = self->level.score.score;
  if (self->game_info.score >= self->game_info.high_score) {
    self->game_info.high_score = self->game_info.score;
  }
}

/**
 * @brief Обновляет уровень в игровой информации
 * @param self Указатель на объект игры
 */
void _updateTetrisLevel(Tetris_t *self) {
  long tick = self->timer.tick;
  if (self->level.level > self->game_info.level &&
      tick >= self->timer.default_tick) {
    self->game_info.speed += self->speed_diff;
    self->timer.tick -= self->tick_diff;
  }
  self->game_info.level = self->level.level;
}

/**
 * @brief Основная функция обновления состояния игры
 * @param self Указатель на объект игры
 */
void _updateTetrisState(Tetris_t *self) {
  clearTetraminoFromField(self);
  if (self->state == TETRIS_STATE_MOVE) {
    if (self->timer.calcDiff(&self->timer) >= self->timer.tick) {
      self->down(self, true);
      self->timer.updateLastTime(&self->timer);
    }
  }
  if (self->state == TETRIS_STATE_ATTACH) {
    clearLines(self);
    self->spawn(self);
  }
  insertTetraminoToFieldWithColor(self);
}

/**
 * @brief Ставит игру на паузу
 * @param tetris Указатель на объект игры
 */
void _pauseGame(Tetris_t *tetris) {
  tetris->game_info.pause = PAUSE_MODE_PAUSE;
  tetris->state = TETRIS_STATE_PAUSE;
}

/**
 * @brief Завершает игру и освобождает ресурсы
 * @param self Указатель на объект игры
 */
void _exitGame(Tetris_t *self) {
  self->db.write(&self->db, self->game_info.high_score);
  self->game_info.pause = PAUSE_MODE_EXIT;
  self->state = TETRIS_STATE_EXIT;

  freeField(&self->game_info.field, FIELD_HEIGHT + FIELD_BORDER);
  freeField(&self->game_info.next, TETRAMINO_HEIGHT);
  self->next_tetramino = NULL;
}

/**
 * @brief Назначает функции-обработчики для объекта игры
 * @param self Указатель на объект игры
 */
void assignFunctionPointers(Tetris_t *self) {
  self->start = _startGame;
  self->spawn = _spawn;
  self->action = _action;
  self->left = _left;
  self->right = _right;
  self->up = _up;
  self->down = _down;
  self->pause = _pauseGame;
  self->exit = _exitGame;
  self->restoreInfo = _restoreInfo;
  self->updateScore = _updateTetrisScore;
  self->updateLevel = _updateTetrisLevel;
  self->updateTetrisState = _updateTetrisState;
}

/**
 * @brief Создает и инициализирует объект игры
 * @return Инициализированный объект игры
 */
Tetris_t constructorTetris() {
  Tetris_t self = (Tetris_t){.state = TETRIS_STATE_START,
                             .game_info = initGameInfo(),
                             .curr_tetramino = initCurrentTetramino(),
                             .next_tetramino = NULL,
                             .collection = initTetraminoCollection(),
                             .timer = initTimer(),
                             .level = initLevel(),
                             .db = initDataBase("tetris_db.txt"),
                             .speed_diff = TETRIS_SPEED_INCREMENT,
                             .tick_diff = TETRIS_TICK_DECREMENT};

  assignFunctionPointers(&self);
  clearField(self.game_info.field);
  return self;
}

/**
 * @brief Инициализирует и возвращает указатель на объект игры
 * @return Указатель на статический объект игры
 *
 * @note Использует статическую переменную для реализации singleton
 */
Tetris_t *initTetris() {
  static Tetris_t tetris;
  static bool initialized = false;

  if (!initialized) {
    tetris = constructorTetris();
    initialized = true;
  }

  return &tetris;
}
