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
  this->helpPanel.draw(&this->helpPanel);
  this->scorePanel.draw(&this->scorePanel);
  this->levelPanel.draw(&this->levelPanel);
  this->nextFigurePanel.draw(&this->nextFigurePanel);
}

Window_t _constructorWindow() {
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
     .draw = _drawWindow
   }; 
}


