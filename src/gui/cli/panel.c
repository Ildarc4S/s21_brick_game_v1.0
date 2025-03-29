#include "./include/panel.h"

void drawPanelHead(Panel_t *self) {
  attron(COLOR_PAIR(self->color));
  mvprintw(self->y - 1, (self->x) * PANEL_CELL_WIDTH, "%s", self->head_text);
  attroff(COLOR_PAIR(self->color));
}

void drawFigure(Panel_t *self, GameInfo_t game_info) {
  if (!game_info.next) return;
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      mvprintw(self->y + i + 1, (self->x + j + 1) * PANEL_CELL_WIDTH, "  ");
      if (game_info.next[i][j]) {
        attron(COLOR_PAIR(game_info.next[i][j]));
        mvprintw(self->y + i + 1, (self->x + j + 1) * PANEL_CELL_WIDTH, "[]");
        attroff(COLOR_PAIR(game_info.next[i][j]));
      }
    }
  }
}

void drawText(Panel_t *self) {
  GameInfo_t game_info = updateCurrentState();
  int start = game_info.next ? PANEL_TETRIS_HELP_TEXT_START
                             : PANEL_SNAKE_HELP_TEXT_START;
  int count = game_info.next ? PANEL_TETRIS_HELP_TEXT_COUNT
                             : PANEL_SNAKE_HELP_TEXT_COUNT;
  for (int i = 0; i < count && (start + i) < self->size; i++) {
    mvprintw(self->y + i, self->x * PANEL_CELL_WIDTH, "%s",
             self->text[start + i]);
  }
}

void _drawPanel(Panel_t *self) {
  GameInfo_t game_info = updateCurrentState();
  if (!(self->mode == PANEL_MODE_NEXT_FIGURE && !game_info.next)) {
    drawPanelHead(self);
  }
  mvprintw(self->y, (self->x) * PANEL_CELL_WIDTH, "       ");
  switch (self->mode) {
    case PANEL_MODE_TEXT:
      drawText(self);
      break;
    case PANEL_MODE_HIGH_SCORE:
      mvprintw(self->y, self->x * PANEL_CELL_WIDTH, "%d", game_info.high_score);
      break;
    case PANEL_MODE_SPEED:
      mvprintw(self->y, self->x * PANEL_CELL_WIDTH, "%d", game_info.speed);
      break;
    case PANEL_MODE_LEVEL:
      mvprintw(self->y, self->x * PANEL_CELL_WIDTH, "%d", game_info.level);
      break;
    case PANEL_MODE_CUR_SCORE:
      mvprintw(self->y, self->x * PANEL_CELL_WIDTH, "%d", game_info.score);
      break;
    case PANEL_MODE_NEXT_FIGURE:
      drawFigure(self, game_info);
      break;
  }
}

Panel_t initPanel(int x, int y, const char *title, const char **text, int size,
                  PanelColor_t color, PanelMode_t mode) {
  Panel_t panel = {.x = x,
                   .y = y,
                   .size = size,
                   .mode = mode,
                   .color = color,
                   .draw = _drawPanel};
  strncpy(panel.head_text, title, sizeof(panel.head_text) - 1);
  for (int i = 0; i < size && i < PANEL_TEXT_SIZE; i++) {
    strncpy(panel.text[i], text[i], sizeof(panel.text[i]) - 1);
  }
  return panel;
}
