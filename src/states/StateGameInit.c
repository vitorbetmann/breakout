// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateGameInit.h"
#include "Brick.h"
#include "LevelMaker.h"
#include "_Constants.h"
#include "smile.h"
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
// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_game_init_enter(void *args) {
  gHealth = MAX_HEALTH;
  gScore = 0;
  if (bricks) {
    MapUnload();
  }
  MapCreate();

  sm_change_state(&stateServe, NULL);
}