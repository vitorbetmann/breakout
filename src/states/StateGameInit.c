// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateGameInit.h"
#include "Brick.h"
#include "LevelMaker.h"
#include "Smile.h"
#include "_Constants.h"
#include "states/StateServe.h"

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
extern int currLevel;
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

  SM_ChangeState(&stateServe, NULL);
}