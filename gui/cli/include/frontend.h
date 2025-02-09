#include <ncurses.h>
#include "../../../brick_game/tetris/include/objects.h"

void initColorPairs();
void initNcurses();

void printField(GameInfo_t *game_info);
void printTetramino(Tetramino_t *tetramino);
