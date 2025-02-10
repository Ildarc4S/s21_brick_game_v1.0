#include "include/backend.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

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


void _startGame(struct _tetris_t *tetris) { 
  tetris->state = SPAWN;
  tetris->spawn(tetris);
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
      if (this->info.next_tetramino->brick[i][j]) {
        this->info.game_info.next[i][j] = this->info.next_tetramino->color;
      }
    }
  }
  
  this->state = MOVE;

  if (checkCollideOtherBreak(this, this->info.curr_tetramino)) {
    mvprintw(21, 40, "Game over");
    this->state = GAME_OVER; 
  }

}

void _pauseGame(struct _tetris_t *tetris) { 
  tetris->state = PAUSE;
}

void _exitGame(struct _tetris_t *tetris) { 
  tetris->state = EXIT;
}

void _left(struct _tetris_t *tetris, bool hold) {
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
  (void)hold;
  
  Tetramino_t *tetramino = tetris->info.curr_tetramino; 
  tetramino->y++;
  int is_collide = 0;
  if (isCollide(tetris, tetramino)) {
    is_collide = 1;
    tetramino->y--;
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

void userInput(UserAction_t action, int hold) {
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
     case SPAWN:
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;

         default:
           break;
       };
     case MOVE: 
     case SHIFT: 
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
       mvprintw(19, 40, "State");
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

Tetris_t* createTetris() {
  Tetris_t *tetris_self = (Tetris_t*)malloc(sizeof(Tetris_t));
  
  tetris_self->state = START;
  tetris_self->info = (TetrisInfo_t) {
    .game_info = (GameInfo_t) { 
      .field = newField(FIELD_WIDTH + 2,FIELD_HEIGHT + 2),
      .next = newField(TETRAMINO_WIDTH, TETRAMINO_HEIGHT),
      .score = 0,
      .high_score = 0,
      .level = 1,
      .speed = 0,
      .pause = 0
    },
    .last_time = 0,
    .curr_tetramino = NULL,
    .next_tetramino = NULL
  };
  tetris_self->left = _left; 
  tetris_self->right = _right; 
  tetris_self->down = _down; 
  tetris_self->up = _up; 
  tetris_self->action = _action; 
  tetris_self->start = _startGame;
  tetris_self->spawn = _spawn;
  tetris_self->exit = _exitGame; 
  tetris_self->pause = _pauseGame; 
  tetris_self->collection = initTetraminoCollection();

  return tetris_self;
}

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

GameInfo_t updateCurrentState() {
  Tetris_t *tetris = initTetris();
  if (tetris->state == MOVE) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);  
    if (timeDiff(tetris->info.last_time, current_time) >= 1010) {
      tetris->down(tetris, 0);
      tetris->info.last_time = current_time;  // Обновление времени последнего вызова
    }
  } else if (tetris->state == ATTACH) {
    tetris->spawn(tetris);
  }
  return tetris->info.game_info;
}


