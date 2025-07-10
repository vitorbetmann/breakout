// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateGameInit.h"
#include "Brick.h"
#include "LevelMaker.h"
#include "Smile.h"
#include "_Constants.h"
#include "states/StateServe.h"
#include <stdlib.h>

// --------------------------------------------------
// Variables
// --------------------------------------------------
State stateGameInit = {.id = "game init",
                       .enter = state_game_init_enter,
                       .update = NULL,
                       .draw = NULL,
                       .exit = NULL};
extern int gHealth;
extern int gScore;
extern unsigned int currLevel;
// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_game_init_enter(void *args) {
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

  SM_ChangeState(&stateServe, &stateServeArgs);
}