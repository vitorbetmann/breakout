// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Dependencies.h"

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern int gHealth;
extern int gScore;
extern int currLevel;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StateInitEnter(void *args) {
  gHealth = MAX_HEALTH;
  gScore = 0;
  if (bricks) {
    MapUnload();
  }
  MapCreate(currLevel);

  StateServeArgs stateServeArgs = {.brickCount = 0};
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      if (bricks[i][j] && bricks[i][j]->inPlay) {
        stateServeArgs.brickCount++;
      }
    }
  }

  SM_ChangeStateTo("serve", &stateServeArgs);
}