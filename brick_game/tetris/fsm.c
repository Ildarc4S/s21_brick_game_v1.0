#include "include/backend.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "./include/timer.h"


Tetris_t* createTetris();
void actionProcess(UserAction_t action, Tetris_t* tetris, int hold);

void getRealBrickSize(Tetramino_t* tetramino, int* min_x, int* max_x, int* max_y) {
  *min_x = 4;
  *max_x = -1;
  *max_y = -1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetramino->brick[i][j]) {
        if (j < *min_x)
          *min_x = j;
        if (j > *max_x)
          *max_x = j;
        if (i > *max_y) 
          *max_y = i;
      }
    }
  }
}

int checkCollideOtherBreak(Tetris_t *tetris, Tetramino_t *tetramino) {
  int result_code = 0;
  int x = tetramino->x;
  int y = tetramino->y;

  for (int i = 0; i < TETRAMINO_HEIGHT && !result_code; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH && !result_code; j++) {
      if (tetramino->brick[i][j]) {
        int field_x = x + j;
        int field_y = y + i;
        
        if (tetris->info.game_info.field[field_y][field_x] && tetramino->brick[i][j]) {
          result_code = 1;
        }
      }
    }
  }
  return result_code;
}

void checkCollideSide(Tetris_t *tetris, Tetramino_t *tetramino, int min_x, int max_x, int max_y,
                   int *collide_left_x, int *collide_right_x, int *collide_bottom_y) {
  if (min_x <= 0) {
    *collide_left_x = 1;
  }
  
  if (max_x >= FIELD_WIDTH + 1) {
    *collide_right_x = 1;
  }

  if (max_y >= FIELD_HEIGHT + 1 || checkCollideOtherBreak(tetris, tetramino)) {
    *collide_bottom_y = 1;
  }
}

void collideProcess(Tetris_t *tetris, Tetramino_t *tetramino, int *collide_left_x, int *collide_right_x, int *collide_bottom_y) {
  int min_x = 0;
  int max_x = 0;
  int max_y = 0;
 
  getRealBrickSize(tetramino, &min_x, &max_x, &max_y);

  max_x = tetramino->x + max_x;
  min_x = tetramino->x + min_x;
  max_y = tetramino->y + max_y;

  checkCollideSide(tetris, tetramino, min_x, max_x, max_y, collide_left_x, collide_right_x, collide_bottom_y);
}

int isCollide(Tetris_t *tetris, Tetramino_t *tetramino) {
  int collide_left_x = 0;
  int collide_right_x = 0;
  int collide_bottom_y = 0;
  collideProcess(tetris, tetramino, &collide_left_x, &collide_right_x, &collide_bottom_y);

  return collide_left_x || collide_right_x || collide_bottom_y;
}

void replaceTetramin(Tetris_t *tetris, Tetramino_t *tetramino) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      tetris->info.curr_tetramino->brick[i][j] = tetramino->brick[i][j]; 
    }
  }
  tetris->info.curr_tetramino->x = tetramino->x;
  tetris->info.curr_tetramino->y = tetramino->y;
}

void insertBrick(Tetris_t *tetris) {
  int x = tetris->info.curr_tetramino->x;
  int y = tetris->info.curr_tetramino->y;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      if (tetris->info.curr_tetramino->brick[i][j]) {
        tetris->info.game_info.field[y + i][x + j] = tetris->info.curr_tetramino->brick[i][j];
      }
    }
  }
}

void copyBrick(int brick_one[4][4], int brick_two[4][4]) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      brick_one[i][j] = brick_two[i][j]; 
    }
  }
}

void rotateTetramino(Tetramino_t* tetramino) {
  int temp[4][4];
  copyBrick(temp, tetramino->brick);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
     for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      temp[j][TETRAMINO_WIDTH - i - 1] = tetramino->brick[i][j];
    }
  }
  copyBrick(tetramino->brick, temp);
}


void _startGame(Tetris_t *tetris) { 
  if (tetris->state == START) {
    tetris->info.game_info.pause = 0;
    tetris->state = SPAWN;
    tetris->spawn(tetris);
    tetris->info.game_info.high_score = tetris->db.read(&tetris->db);
  } else if (tetris->state == PAUSE) {
    tetris->info.game_info.pause = 0;
    tetris->state = MOVE;
  } else if (tetris->state == GAME_OVER) {
    tetris->info.game_info.pause = 0;
    tetris->state = SPAWN;
    fillField(tetris->info.game_info.field);
    tetris->spawn(tetris);
  }
  mvprintw(40, 30, "PAUSE: %d, STATE: %d", tetris->info.game_info.pause, tetris->state);
}

void _spawn(Tetris_t *this) {
  if (!this) return;


  if (!this->info.next_tetramino) {
    this->info.next_tetramino = this->collection->getRandomTetranimo(this->collection);
  }
  
  this->info.curr_tetramino = this->info.next_tetramino;
  this->info.curr_tetramino->x = FIELD_WIDTH/2;
  this->info.curr_tetramino->y = 1;
  
  this->info.next_tetramino = this->collection->getRandomTetranimo(this->collection);
  
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0;  j < TETRAMINO_WIDTH; j++) {
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
  if (!tetris) return;
  (void)hold;
  
  Tetramino_t *tetramino= tetris->info.curr_tetramino; 
  tetramino->x--;
  if (isCollide(tetris, tetramino)) {
    tetramino->x++;
  }
  replaceTetramin(tetris, tetramino);
}

void _right(Tetris_t *tetris, bool hold) {
  if (!tetris) return;
  (void)hold;
  
  Tetramino_t *tetramino= tetris->info.curr_tetramino; 
  tetramino->x++;
  if (isCollide(tetris, tetramino)) {
    tetramino->x--;
  }
  replaceTetramin(tetris, tetramino);
}

void _up(Tetris_t *tetris, bool hold) {
   if (!tetris) return;
  (void)hold;
}

void _down(Tetris_t *tetris, bool hold) {
  if (!tetris) return;
  
  Tetramino_t *tetramino = tetris->info.curr_tetramino; 
  int is_collide = 0;
  
  if (!hold) {
    tetramino->y++;
    if (isCollide(tetris, tetramino)) {
      is_collide = 1;
      tetramino->y--;
    } 
  } else {
    while(!isCollide(tetris, tetramino)) {
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
void computeCollisionSides(Tetris_t *tetris, Tetramino_t *tetramino, 
                           int *collide_left_x, int *collide_right_x, 
                           int *collide_top_y, int *collide_bottom_y) {
  if (!tetris || !tetramino) return;

  // Сбрасываем флаги столкновения
  *collide_left_x = *collide_right_x = *collide_top_y = *collide_bottom_y = -1;

  int min_x, max_x, min_y, max_y;
  
  // Получаем реальные размеры фигуры
  getRealBrickSize(tetramino, &min_x, &max_x, &max_y);
  min_x += tetramino->x;
  max_x += tetramino->x;
  max_y += tetramino->y;
  min_y = tetramino->y; // Верхняя граница фигуры (минимальный Y)

  int **matrix = tetris->info.game_info.field; // Игровое поле

  // Проверка столкновения с левой стенкой
  if (min_x < 0) {
    *collide_left_x = min_x;
  } else {
    for (int y = min_y; y <= max_y; y++) {
      if (matrix[y][min_x] != 0) { // Если клетка занята
        *collide_left_x = min_x;
        break;
      }
    }
  }

  // Проверка столкновения с правой стенкой
  if (max_x >= FIELD_WIDTH) {
    *collide_right_x = max_x;
  } else {
    for (int y = min_y; y <= max_y; y++) {
      if (matrix[y][max_x] != 0) {
        *collide_right_x = max_x;
        break;
      }
    }
  }

  // Проверка столкновения с нижней границей
  if (max_y >= FIELD_HEIGHT) {
    *collide_bottom_y = max_y;
  } else {
    for (int x = min_x; x <= max_x; x++) {
      if (matrix[max_y][x] != 0) {
        *collide_bottom_y = max_y;
        break;
      }
    }
  }

  // Проверка столкновения с верхней границей (например, при появлении)
  if (min_y < 0) {
    *collide_top_y = min_y;
  } else {
    for (int x = min_x; x <= max_x; x++) {
      if (matrix[min_y][x] != 0) {
        *collide_top_y = min_y;
        break;
      }
    }
  }
}

void _action(Tetris_t *tetris, bool hold) {
  if (!tetris) return;
  (void)hold;
  
  Tetramino_t *tetramino = tetris->info.curr_tetramino; 
  int temp[4][4];
  copyBrick(temp, tetramino->brick);
  rotateTetramino(tetramino); 

  if (isCollide(tetris, tetramino)) {
    copyBrick(tetramino->brick, temp);
  }
}

void userInput(UserAction_t action, bool hold) {
   Tetris_t *tetris = initTetris();
   switch (tetris->state) {
     case START:
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;
         case Start:
           tetris->start(tetris);
           break;
         default:
           break;
       };
       break;
     case MOVE: 
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;
         case Pause:
           tetris->pause(tetris);
           break;
         case Left:
           tetris->left(tetris, hold);
           break;
         case Right:
           tetris->right(tetris, hold);
           break;
         case Up:
           tetris->up(tetris, hold);
           break;
         case Down:
           tetris->down(tetris, hold);
           break;
         case Action:
           tetris->action(tetris, hold);
           break;

         default:
           break;
       };
       break;
    case PAUSE:
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;
         case Start:
           tetris->start(tetris);
           break;
         case Pause:
           tetris->pause(tetris);
           break;

         default:
           break;
       };
       break;
    case GAME_OVER: 
       switch (action) {
         case Start:
           tetris->start(tetris);
           break;
         case Terminate:
           tetris->exit(tetris);
           break;
         
         default:
           break;
       };
       break;

    default:
      break;
   };
}

void createBrick(Tetris_t *tetris) {
  int r[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  tetris->info.curr_tetramino = malloc(sizeof(Tetramino_t));
  
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      tetris->info.curr_tetramino->brick[i][j] = r[i][j];
    }
  }
}

void _updateTetrisScore(Tetris_t *this) {
  this->info.game_info.score = this->level.score.getScore(&this->level.score);
  if (this->info.game_info.score >= this->info.game_info.high_score) {
    this->info.game_info.high_score = this->info.game_info.score; 
  }
}

void _updateTetrisLevel(Tetris_t *this) {
  this->info.game_info.level = this->level.getLevel(&this->level);
}

Tetris_t* createTetris() {
  Tetris_t *tetris_self = (Tetris_t*)malloc(sizeof(Tetris_t));
  if (!tetris_self) return NULL; 

  tetris_self->state = START;
  tetris_self->info = (TetrisInfo_t) { 
    .game_info = {  
      .field = newField(FIELD_WIDTH + 2, FIELD_HEIGHT + 2),
      .next = newField(TETRAMINO_WIDTH, TETRAMINO_HEIGHT),
      .score = 0,
      .high_score = 0,
      .level = 1,
      .speed = 0,
      .pause = 2
    },
    .curr_tetramino = NULL,
    .next_tetramino = NULL
  };
  fillField(tetris_self->info.game_info.field);
  
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
    tetris = createTetris();
  }
  return tetris;
}

long timeDiff(struct timeval start, struct timeval end) {
  return (end.tv_sec - start.tv_sec) * 1000 +
         (end.tv_usec - start.tv_usec) / 1000;
}

void shiftLines(int *i, Tetris_t *this) {
  for (int k = *i; k > 1; k--) {
    for (int j = 1; j <= FIELD_WIDTH; j++) {
      this->info.game_info.field[k][j] = this->info.game_info.field[k - 1][j];
    }
  }
  *i += 1; 
}

void cleanLines(Tetris_t *this) {
  int erase_line_count = 0;
  for (int i = FIELD_HEIGHT; i > 0; i--) {
    int erase_line = 1;
    for (int j = 1; j < FIELD_WIDTH + 1; j++) {
      if (this->info.game_info.field[i][j] == 0) {
        erase_line = 0;
      }
    }
    if (erase_line) {
      erase_line_count++;
      shiftLines(&i, this);
    }
  }

  Score_t score = constructorScore();
  score.convertLineCountToScore(&score, erase_line_count);

  this->level.setScore(&this->level, &score);
  this->level.updateLevel(&this->level);

  this->updateScore(this);
  this->updateLevel(this);
}

GameInfo_t updateCurrentState() {
  Tetris_t *tetris = initTetris();
  if (tetris->state == MOVE) {
    if (tetris->timer.calcDiff(&tetris->timer) >= tetris->timer.getTick(&tetris->timer)) {
      tetris->down(tetris, 0);
      tetris->timer.updateLastTime(&tetris->timer);
    }
  } else if (tetris->state == ATTACH) {
    tetris->spawn(tetris);
    cleanLines(tetris);
  }
  return tetris->info.game_info;
}


