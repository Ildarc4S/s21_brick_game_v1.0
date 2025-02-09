#ifndef TETRAMINO_H
#define TETRAMINO_H

typedef enum {
  COLOR_RED,
  COLOR_YELLOW,
  COLOR_ORANGE,
  COLOR_BLUE,
  COLOR_GREEN,
  COLOR_PINK,
  COLOR_PURPLE
} Color;

typedef struct {
  int x;
  int y;
  Color color;
  int brick[4][4];
} Tetramino_t;

#endif
