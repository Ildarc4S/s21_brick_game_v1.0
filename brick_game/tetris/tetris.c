#include "./include/tetris.h"
#include "./include/tetris_utils.h"

void _startGame(Tetris_t *tetris) {
  if (tetris->state == START) {
    tetris->info.game_info.pause = 0;
    tetris->spawn(tetris);
    tetris->info.game_info.high_score = tetris->db.read(&tetris->db);
  } else if (tetris->state == PAUSE) {
    tetris->info.game_info.pause = 0;
    tetris->state = MOVE;
  } else if (tetris->state == GAME_OVER) {
    cleanField(tetris->info.game_info.field);

    tetris->timer.tick = 1000;
    tetris->level.level = 1;
    tetris->level.score.score = 0;

    tetris->info.game_info.level = 1;
    tetris->info.game_info.score = 1;
    tetris->info.game_info.pause = 0;
    tetris->info.game_info.speed = 10;
    tetris->spawn(tetris);
  }
}

void _spawn(Tetris_t *this) {
  if (!this)
    return;

  if (!this->info.next_tetramino) {
    this->info.next_tetramino =
        this->collection->getRandomTetranimo(this->collection);
  }

  this->info.curr_tetramino = this->info.next_tetramino;
  this->info.curr_tetramino->x = FIELD_WIDTH / 2;
  this->info.curr_tetramino->y = 1;

  this->info.next_tetramino =
      this->collection->getRandomTetranimo(this->collection);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      this->info.game_info.next[i][j] = 0;
      if (this->info.next_tetramino->brick[i][j]) {
        this->info.game_info.next[i][j] = this->info.next_tetramino->color;
      }
    }
  }

  this->state = MOVE;

  if (checkCollideOtherBreak(this, this->info.curr_tetramino)) {
    this->info.game_info.pause = -1;
    this->db.write(&this->db, this->info.game_info.high_score);
    this->state = GAME_OVER;
  }
}

void _pauseGame(Tetris_t *tetris) {
  tetris->info.game_info.pause = 1;
  tetris->state = PAUSE;
}

void _exitGame(Tetris_t *this) {
  this->db.write(&this->db, this->info.game_info.high_score);
  this->state = EXIT;
}

void _left(Tetris_t *tetris, bool hold) {
  if (!tetris)
    return;
  (void)hold;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  tetramino->x--;
  if (isCollide(tetris, tetramino)) {
    tetramino->x++;
  }
  replaceTetramin(tetris, tetramino);
}

void _right(Tetris_t *tetris, bool hold) {
  if (!tetris)
    return;
  (void)hold;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  tetramino->x++;
  if (isCollide(tetris, tetramino)) {
    tetramino->x--;
  }
  replaceTetramin(tetris, tetramino);
}

void _up(Tetris_t *this, bool hold) {
  if (!this) {
    return;
  }
  (void)hold;
}

void _down(Tetris_t *tetris, bool hold) {
  if (!tetris)
    return;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  int is_collide = 0;

  if (hold == 0) {
    tetramino->y++;
    if (isCollide(tetris, tetramino)) {
      is_collide = 1;
      tetramino->y--;
    }
  } else {
    while (!isCollide(tetris, tetramino)) {
      tetramino->y++;
    }
    tetramino->y--;
    is_collide = 1;
  }
  replaceTetramin(tetris, tetramino);
  if (is_collide) {
    tetris->state = ATTACH;
    insertBrick(tetris);
    tetris->info.curr_tetramino = NULL;
  }
}

void _action(Tetris_t *tetris, bool hold) {
  if (!tetris)
    return;
  (void)hold;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  int temp[4][4];
  copyBrick(temp, tetramino->brick);
  rotateTetramino(tetramino);

  if (isCollide(tetris, tetramino)) {
    copyBrick(tetramino->brick, temp);
  }
}

void _updateTetrisScore(Tetris_t *this) {
  this->info.game_info.score = this->level.score.getScore(&this->level.score);
  if (this->info.game_info.score >= this->info.game_info.high_score) {
    this->info.game_info.high_score = this->info.game_info.score;
  }
}

void _updateTetrisLevel(Tetris_t *this) {
  long tick = this->timer.getTick(&this->timer);
  if (this->level.getLevel(&this->level) > this->info.game_info.level &&
      tick >= 80) {
    this->info.game_info.speed += 10;
    this->timer.setTick(&this->timer, tick - 70);
  }
  this->info.game_info.level = this->level.getLevel(&this->level);
}

void _destructorTetris(Tetris_t *this) {
  this->info.next_tetramino = NULL;
  this->info.curr_tetramino = NULL;

  if (this->info.game_info.field) {
    freeField(this->info.game_info.field, FIELD_HEIGHT + 2);
    this->info.game_info.field = NULL;
  }

  if (this->info.game_info.next) {
    freeField(this->info.game_info.next, TETRAMINO_HEIGHT);
    this->info.game_info.next = NULL;
  }

  if (this->collection) {
    this->collection->destructor(this->collection);
    this->collection = NULL;
  }
  free(this);
}

Tetris_t *constructorTetris() {
  Tetris_t *tetris_self = (Tetris_t *)malloc(sizeof(Tetris_t));
  if (!tetris_self)
    return NULL;

  tetris_self->state = START;
  tetris_self->info = (TetrisInfo_t){
      .game_info = {.field = newField(FIELD_WIDTH + 2, FIELD_HEIGHT + 2),
                    .next = newField(TETRAMINO_WIDTH, TETRAMINO_HEIGHT),
                    .score = 0,
                    .high_score = 0,
                    .level = 1,
                    .speed = 0,
                    .pause = 2},
      .curr_tetramino = NULL,
      .next_tetramino = NULL};
  cleanField(tetris_self->info.game_info.field);

  tetris_self->db = initDatabase("./brick_game/db/tetris_db.txt");
  tetris_self->level = constructorLevel();
  tetris_self->timer = constructorTimer(),

  tetris_self->left = _left;
  tetris_self->right = _right;
  tetris_self->down = _down;
  tetris_self->up = _up;
  tetris_self->action = _action;
  tetris_self->start = _startGame;
  tetris_self->spawn = _spawn;
  tetris_self->exit = _exitGame;
  tetris_self->pause = _pauseGame;
  tetris_self->destructor = _destructorTetris;

  tetris_self->updateLevel = _updateTetrisLevel;
  tetris_self->updateScore = _updateTetrisScore;

  tetris_self->collection = initTetraminoCollection();

  return tetris_self;
}

// -1 - GAME_OVER
// 0 - MOVE
// 1 - PAUSE
// 2 - start

Tetris_t *initTetris() {
  static Tetris_t *tetris = NULL;
  if (!tetris) {
    tetris = constructorTetris();
  }
  return tetris;
}

GameInfo_t updateCurrentState() {
  Tetris_t *tetris = initTetris();
  if (tetris->state == MOVE) {
    if (tetris->timer.calcDiff(&tetris->timer) >=
        tetris->timer.getTick(&tetris->timer)) {
      tetris->down(tetris, 0);
      tetris->timer.updateLastTime(&tetris->timer);
    }
  } else if (tetris->state == ATTACH) {
    tetris->spawn(tetris);
    cleanLines(tetris);
  }
  return tetris->info.game_info;
}
