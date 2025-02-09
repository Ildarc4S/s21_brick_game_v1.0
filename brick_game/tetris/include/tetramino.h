#ifndef TETRAMINO_H
#define TETRAMINO_H

typedef enum {
  TETRAMINO_COLOR_RED,
  TETRAMINO_COLOR_YELLOW,
  TETRAMINO_COLOR_ORANGE,
  TETRAMINO_COLOR_BLUE,
  TETRAMINO_COLOR_GREEN,
  TETRAMINO_COLOR_PINK,
  TETRAMINO_COLOR_PURPLE
} Color;

typedef struct {
  int x;
  int y;
  Color color;
  int brick[4][4];
} Tetramino_t;

#endif
