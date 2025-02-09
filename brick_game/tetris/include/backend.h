#ifndef BACKEND_H
#define BACKEND_H

#include "objects.h"

int** newField(int width, int height);
void freeField(int** field, int height);

void createBrick(Tetris_t *tetris);
void fillField(int **field);
void printField(GameInfo_t* game_info);

Tetris_t* createTetris();
void actionProcess(UserAction_t action, Tetris_t* tetris, int hold);

#endif // BACKEND_H
