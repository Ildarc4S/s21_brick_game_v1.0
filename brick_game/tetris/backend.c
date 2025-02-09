#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/backend.h"


void fillField(int** field) {
  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
      if ( i == 0 || j == 0 || i == FIELD_HEIGHT + 1 || j == FIELD_WIDTH + 1) {
        field[i][j] = 1;
      }
    }
  }
}

int** newField(int width, int height) {
  int result_code = 0;
  int** field = (int **)calloc(height + 2, sizeof(int *));
  if (field == NULL) {
    result_code = 1;
  }

  for (int i = 0; i < height && result_code != 1; i++) {
    field[i] = (int *)calloc(width, sizeof(int));
    if (field[i] == NULL) {
      result_code = 1;
    }
  }

  if (result_code == 1) {
    freeField(field, height);
  }
  return field;
}

void freeField(int** field, int height) {
  if (field == NULL) {
    return;
  }
  for (int i = 0; i < height; i++) {
    free(field[i]);
    field[i] = NULL;
  }
  free(field);
  field = NULL;
}

void createTetraminos(Tetramino_t *tetraminos) {
  const int figures[7][4][4] = {
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // O
      {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}, // T
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, // S
      {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // Z
      {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}, // J
      {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}  // L
  };

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      memcpy(tetraminos[i].brick[j], figures[i][j], sizeof(figures[i][j]));
    }
    tetraminos[i].x = 0;
    tetraminos[i].y = 0;
  }
}


