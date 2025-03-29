#include "./include/game_field.h"

void drawCleanField(GameField_t *self) {
  for (int i = 0; i < self->height; i++) {
    for (int j = 0; j < self->width; j++) {
      if (i == self->height - 1 || j == self->width - 1 || i == 0 || j == 0) {
        mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "[]");
      } else {
        mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "  ");
      }
    }
  }
}

bool isTetraminoCode(int field_code) {
  return field_code == OBJECT_CODE_TETRAMINO_I ||
         field_code == OBJECT_CODE_TETRAMINO_O ||
         field_code == OBJECT_CODE_TETRAMINO_T ||
         field_code == OBJECT_CODE_TETRAMINO_S ||
         field_code == OBJECT_CODE_TETRAMINO_Z ||
         field_code == OBJECT_CODE_TETRAMINO_J ||
         field_code == OBJECT_CODE_TETRAMINO_L;
}

static void clearField(GameField_t *self) {
  for (int i = 0; i < self->height; i++) {
    for (int j = 0; j < self->width; j++) {
      mvprintw(self->y + i, (self->x + j) * GAME_FIELD_CELL_WIDTH, "  ");
    }
  }
}

void drawCell(int y, int x, const char *symbol, int color_pair) {
  if (color_pair > 0) {
    attron(COLOR_PAIR(color_pair));
  }
  mvprintw(y, x, "%s", symbol);
  if (color_pair > 0) {
    attroff(COLOR_PAIR(color_pair));
  }
}

void drawActiveGame(GameField_t *self, GameInfo_t *game) {
  for (int i = 0; i < self->height; i++) {
    for (int j = 0; j < self->width; j++) {
      int pos_y = self->y + i;
      int pos_x = (self->x + j) * GAME_FIELD_CELL_WIDTH;
      int cell_value = game->field[i][j];

      if (cell_value == OBJECT_CODE_WALL) {
        drawCell(pos_y, pos_x, "[]", 0);
      } else if (cell_value == OBJECT_CODE_AIR) {
        drawCell(pos_y, pos_x, "  ", 0);
      } else if (cell_value == OBJECT_CODE_APPLE) {
        drawCell(pos_y, pos_x, "()", 0);
      } else if (isTetraminoCode(cell_value) ||
                 cell_value == OBJECT_CODE_SNAKE) {
        drawCell(pos_y, pos_x, "[]", cell_value);
      }
    }
  }
}

void drawGameStateMessage(GameField_t *self, const char *message) {
  drawCleanField(self);
  int centerY = self->height / GAME_FIELD_CENTER_DIVISOR;
  int centerX =
      ((self->width - GAME_FIELD_CENTER_OFFSET) / GAME_FIELD_CENTER_DIVISOR) *
      GAME_FIELD_CELL_WIDTH;
  mvprintw(centerY, centerX, "%s", message);
}

void _drawField(GameField_t *self) {
  GameInfo_t game = updateCurrentState();

  clearField(self);

  switch (game.pause) {
    case PAUSE_MODE_GAME_CONTINUE:
      drawActiveGame(self, &game);
      break;

    case PAUSE_MODE_START:
      drawGameStateMessage(self, "START");
      break;

    case PAUSE_MODE_PAUSE:
      drawGameStateMessage(self, "PAUSE");
      break;

    case PAUSE_MODE_GAME_OVER:
      drawGameStateMessage(self, "GAME_OVER");
      break;
  }
}
GameField_t initGameField(int width, int height) {
  return (GameField_t){
      .x = GAME_FIELD_GAME_FIELD_INIT_X,
      .y = GAME_FIELD_GAME_FIELD_INIT_Y,
      .width = width,
      .height = height,
      .drawField = _drawField,
  };
}
