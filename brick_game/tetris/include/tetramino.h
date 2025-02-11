#ifndef TETRAMINO_H
#define TETRAMINO_H

#define TETRAMINO_WIDTH 4
#define TETRAMINO_HEIGHT 4

typedef enum {
  TETRAMINO_COLOR_RED = 2,
  TETRAMINO_COLOR_YELLOW,   // 3
  TETRAMINO_COLOR_CYAN,     // 4
  TETRAMINO_COLOR_BLUE,     // 5
  TETRAMINO_COLOR_GREEN,    // 6
  TETRAMINO_COLOR_MAGNETA,  // 7
} Color;

typedef struct {
  int x;
  int y;
  Color color;
  int brick[4][4];
} Tetramino_t;

#endif  // TETRAMINO_H
