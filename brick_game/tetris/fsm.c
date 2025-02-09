#include "include/backend.h"
#include <stdlib.h>
#include <stdbool.h>

Tetris_t* createTetris();
void actionProcess(UserAction_t action, Tetris_t* tetris, int hold);

void _start_game(struct _tetris_t *tetris) { 
  tetris->state = SPAWN;
}

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

int isCollide(Tetramino_t *tetramino) {
  int result_code = 0;
  int min_x = 0;
  int max_x = 0;
  int max_y = 0;

  getRealBrickSize(tetramino, &min_x, &max_x, &max_y);

  max_x = tetramino->x + max_x;
  min_x = tetramino->x + min_x;
  max_y = tetramino->y + max_y;
  
  if (min_x <= 0 || max_x >= FIELD_WIDTH + 1 || max_y >= FIELD_HEIGHT + 1) {
    result_code = 1; 
  }

  return result_code;
}

void replaceTetramin(Tetris_t *tetris, Tetramino_t *tetramino) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      tetris->info.curr_tetramino->brick[i][j] = tetramino->brick[i][j]; 
    }
  }
}

void _left(struct _tetris_t *tetris, bool hold) {
  if (!tetris) return;
  (void)hold;
  
  Tetramino_t *tetramino= tetris->info.curr_tetramino; 
  tetramino->x--;
  if (isCollide(tetramino)) {
    tetramino->x++;
  }
  replaceTetramin(tetris, tetramino);
}


void _right(Tetris_t *tetris, bool hold) {
  if (!tetris) return;
  (void)hold;
  
  Tetramino_t *tetramino= tetris->info.curr_tetramino; 
  tetramino->x++;
  if (isCollide(tetramino)) {
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
  
  Tetramino_t *tetramino= tetris->info.curr_tetramino; 
  tetramino->y++;
  if (isCollide(tetramino)) {
    tetramino->y--;
  }
  replaceTetramin(tetris, tetramino);
}


void _action(Tetris_t *tetris, bool hold);

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
  //tetris_self->action = _action; 
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
  
}


