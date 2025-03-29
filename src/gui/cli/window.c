#include "./include/window.h"

void _drawWindow(Window_t *self) {
  self->game_field.drawField(&self->game_field);
  self->help_panel.draw(&self->help_panel);
  self->score_panel.draw(&self->score_panel);
  self->high_score_panel.draw(&self->high_score_panel);
  self->level_panel.draw(&self->level_panel);
  self->next_figure_panel.draw(&self->next_figure_panel);
  self->speed_panel.draw(&self->speed_panel);
}

bool _checkGameExit() {
  GameInfo_t game_info = updateCurrentState();
  return game_info.pause == PAUSE_MODE_EXIT;
}

Window_t initWindow() {
  const char *help_text[] = {"Press q to quit",
                             "Press p to pause",
                             "Press s to start",
                             "Press left/right to move figure",
                             "Press down to move figure down",
                             "Press space to rotate figure",
                             "Press q to quit",
                             "Press p to pause",
                             "Press s to start",
                             "Press left/right to move snake horizontally",
                             "Press up/down to move snake vertically",
                             "Press space to boost snake"};

  return (Window_t){
      .help_panel = initPanel(WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_HELP_Y,
                              "Help:", help_text, WINDOW_TEXT_LINE_COUNT,
                              PANEL_COLOR_GREEN, PANEL_MODE_TEXT),

      .next_figure_panel =
          initPanel(WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_NEXT_FIGURE_Y,
                    "Next figure:", NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                    PANEL_COLOR_BLUE, PANEL_MODE_NEXT_FIGURE),

      .score_panel = initPanel(
          WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_ROW_ONE_Y, "Score:", NULL,
          WINDOW_TEXT_LINE_COUNT_ZERO, PANEL_COLOR_GREEN, PANEL_MODE_CUR_SCORE),

      .high_score_panel =
          initPanel(WINDOW_PANEL_COLUMN_TWO_X, WINDOW_PANEL_ROW_ONE_Y,
                    "High value:", NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                    PANEL_COLOR_RED, PANEL_MODE_HIGH_SCORE),

      .level_panel = initPanel(
          WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_ROW_TWO_Y, "Level:", NULL,
          WINDOW_TEXT_LINE_COUNT_ZERO, PANEL_COLOR_YELLOW, PANEL_MODE_LEVEL),

      .speed_panel = initPanel(
          WINDOW_PANEL_COLUMN_TWO_X, WINDOW_PANEL_ROW_TWO_Y, "Speed:", NULL,
          WINDOW_TEXT_LINE_COUNT_ZERO, PANEL_COLOR_GREEN, PANEL_MODE_SPEED),

      .game_field = initGameField(FIELD_WIDTH + WINDOW_FIELD_BORDER,
                                  FIELD_HEIGHT + WINDOW_FIELD_BORDER),
      .draw = _drawWindow,
      .checkGameExit = _checkGameExit};
}
