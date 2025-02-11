#include "./include/window.h"
#include <ncurses.h>
#include "../../brick_game/tetris/include/objects.h"

void _drawPanelHead(Panel_t *this) {
  attron(COLOR_PAIR(this->color));
  mvprintw(this->y - 1, (this->x)*2, "%s", this->head_text);
  attroff(COLOR_PAIR(this->color));
}

void drawFigure(Panel_t *this, GameInfo_t game_info) {
  if (!this || !game_info.next) return;
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvprintw(this->y + i + 1, (this->x + j + 1) * 2, "  ");
      if (game_info.next[i][j]) {
        attron(COLOR_PAIR(game_info.next[i][j]));
        mvprintw(this->y + i + 1, (this->x + j + 1) * 2, "[]");
        attroff(COLOR_PAIR(game_info.next[i][j]));
      }
    }
  }
} 

void _drawPanel(Panel_t *this) {
  GameInfo_t game_info = updateCurrentState(); 
  _drawPanelHead(this); 

  if (this->size != 0) {
    for (int i = 0; i < this->size; i++) {
      mvprintw(this->y+i, this->x*2, "%s", this->text[i]);
    }
 } else if (this->score != -1) {
      mvprintw(this->y, this->x*2, "%d", game_info.score);
 } else if (this->level != -1) {
      mvprintw(this->y, this->x*2, "%d", game_info.level);
 } else {
    drawFigure(this, game_info);
 }
}

void _drawWindow(Window_t *this) {
  this->game_field.drawField(&this->game_field);
  this->game_field.drawTetramino(&this->game_field);
  this->helpPanel.draw(&this->helpPanel);
  this->scorePanel.draw(&this->scorePanel);
  this->levelPanel.draw(&this->levelPanel);
  this->nextFigurePanel.draw(&this->nextFigurePanel);
}

void drawCleanField(GameField_t *this) {
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      if (i == this->height-1 || j == this->width-1 || i == 0 || j == 0 ) {
        mvprintw(this->y + i, (this->x + j)*2, "[]");
      } else {
        mvprintw(this->y + i, (this->x + j)*2, "  ");
      }
    }
  }
}

void _drawField(GameField_t *this) {
  GameInfo_t game = updateCurrentState();
  if (game.pause == 0) {
    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        if (game.field[i][j]) {
          mvprintw(this->y + i, (this->x + j)*2, "[]");
        } else {
          mvprintw(this->y + i, (this->x + j)*2, "  ");
        }
      }
    }
  } else if (game.pause == 2) {
    drawCleanField(this);
    mvprintw(this->height/2, ((this->width-1)/2)*2, "START");
  } else if (game.pause == 1) {
    drawCleanField(this);
    mvprintw(this->height/2, ((this->width-1)/2)*2, "PAUSE");
  } else if (game.pause == -1) {
    drawCleanField(this);
    mvprintw(this->height/2, ((this->width-1)/2)*2, "GAME_OVER");
  }

}

void _drawTetramino(GameField_t *this) {
  Tetramino_t *tetramino = this->tetris->info.curr_tetramino;
  if (!tetramino) return;
  if (this->tetris->info.game_info.pause != 0) return;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetramino->brick[i][j]) {
        attron(COLOR_PAIR(tetramino->color));
        mvprintw(tetramino->y + i, (tetramino->x + j) * 2, "[]");
        attroff(COLOR_PAIR(tetramino->color));
      }
    }
  }
}


Window_t _constructorWindow(Tetris_t *tetris) {
   return (Window_t) {
     .helpPanel = (Panel_t) {
        .x = 20,
        .y = 1,
        .head_text = "Help:",
        .text = {"Press q to quit",
                 "Press p to pause",
                 "Press left/right/down to move figure",
                 "Press s to start"
        },
        .size = 4,
        .color = PANEL_GREEN_COLOR,
        .score = -1,
        .level = -1,
        .draw = _drawPanel,
     },
     .nextFigurePanel = (Panel_t) {
        .x = 50,
        .y = 1,
        .head_text = "Next fihure:",
        .size = 0,
        .color = PANEL_BLUE_COLOR,
        .score = -1,
        .level = -1,
        .draw = _drawPanel,
     },
     .scorePanel = (Panel_t) {
        .x = 50,
        .y = 10,
        .head_text = "Score:",
        .size = 0,
        .color = PANEL_GREEN_COLOR,
        .score = 0,
        .level = -1,
        .draw = _drawPanel,
     },
     .levelPanel = (Panel_t) {
        .x = 50,
        .y = 20,
        .head_text = "Level:",
        .size = 0,
        .color = PANEL_YELLOW_COLOR,
        .score = -1,
        .level = 0,
        .draw = _drawPanel,
     },
     .game_field = (GameField_t) {
       .x = 0,
       .y = 0,
       .width = FIELD_WIDTH + 2,
       .height = FIELD_HEIGHT + 2,
       .tetris = tetris,
       .drawField = _drawField,
       .drawTetramino = _drawTetramino,
     },
     .draw = _drawWindow
   }; 
}


