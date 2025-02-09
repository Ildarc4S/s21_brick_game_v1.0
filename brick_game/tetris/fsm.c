#include "include/backend.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>


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

int checkCollideOtherBreak(Tetris_t *tetris, Tetramino_t *tetramino, int min_x, int max_x, int max_y) {
  int result_code = 0;
  int x = tetramino->x;
  int y = tetramino->y;

  for (int i = 0; i < TETRAMINO_HEIGHT && !result_code; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH && !result_code; j++) {
      if (tetramino->brick[i][j]) {
        int field_x = x + j;
        int field_y = y + i;
        
        if (tetris->info.game_info.field[field_y][field_x]) {
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

  if (max_y >= FIELD_HEIGHT + 1 || checkCollideOtherBreak(tetris, tetramino, min_x, max_x, max_y)) {
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
    insertBrick(tetris);
  }
}


void _action(Tetris_t *tetris, bool hold) {
  if (!tetris) return;
  (void)hold;
  
  Tetramino_t *tetramino = tetris->info.curr_tetramino; 
  rotateTetramino(tetramino); 

  int collide_left_x = 0;
  int collide_right_x = 0;
  int collide_bottom_y = 0;
  collideProcess(tetris, tetramino, &collide_left_x, &collide_right_x, &collide_bottom_y);
  if (collide_left_x) {
    tetramino->x++;
  }
  if (collide_right_x) {
    tetramino->x--;
  }
  if (collide_bottom_y) {
    tetramino->y--;
  } 
}

void userInput(UserAction_t action, int hold) {
   Tetris_t *tetris = createTetris();
   switch (tetris->state) {
     case START:
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;
           
         default:
           break;
       };
       break;
     case SPAWN:
     case MOVE: 
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;
         case Pause:
           tetris->pause(tetris);
           break;

         default:
           break;
       };
       break;
     case SHIFT: 
       switch (action) {
         case Terminate:
           tetris->exit(tetris);
           break;
         case Pause:
           tetris->pause(tetris);
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
           tetris->spawn(tetris);
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
    .curr_tetramino = NULL,
    .next_tetramino = NULL
  };
  tetris_self->left = _left; 
  tetris_self->right = _right; 
  tetris_self->down = _down; 
  tetris_self->up = _up; 
  tetris_self->action = _action; 
  tetris_self->start = _startGame; 
  tetris_self->exit = _exitGame; 
  tetris_self->pause = _pauseGame; 
  return tetris_self;
}

Tetris_t *initTetris() {
  static Tetris_t *tetris = NULL;
  if (!tetris) {
    tetris = createTetris();
  }
  return tetris;
}

GameInfo_t updateCurrentState() {
  Tetris_t *tetris = initTetris();
  return tetris->info.game_info;
}


