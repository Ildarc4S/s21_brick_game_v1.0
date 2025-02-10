#ifndef TETRAMINO_H
#define TETRAMINO_H

typedef enum {
  TETRAMINO_COLOR_RED = 2,
  TETRAMINO_COLOR_YELLOW,  // 2
  TETRAMINO_COLOR_CYAN,  // 3
  TETRAMINO_COLOR_BLUE,    // 4
  TETRAMINO_COLOR_GREEN,   // 5
  TETRAMINO_COLOR_MAGNETA,    // 6
} Color;

typedef struct {
  int x;
  int y;
  Color color;
  int brick[4][4];
} Tetramino_t;

#endif
