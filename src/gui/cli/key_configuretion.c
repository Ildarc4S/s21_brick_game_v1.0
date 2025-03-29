#include "./include/key_configuration.h"

void upKeyPressed(Button_t btn) { userInput(Up, btn.hold); }
void leftKeyPressed(Button_t btn) { userInput(Left, btn.hold); }
void rightKeyPressed(Button_t btn) { userInput(Right, btn.hold); }
void downKeyPressed(Button_t btn) { userInput(Down, btn.hold); }
void spaceKeyPressed(Button_t btn) { userInput(Action, btn.hold); }
void startKeyPressed(Button_t btn) { userInput(Start, btn.hold); }
void pauseKeyPressed(Button_t btn) { userInput(Pause, btn.hold); }
void exitKeyPressed(Button_t btn) { userInput(Terminate, btn.hold); }
