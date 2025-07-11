// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateHighScore.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------

// --------------------------------------------------
// Variables
// --------------------------------------------------
const State stateHighScore = {.id = "high score",
                              .enter = StateHighScoreEnter,
                              .update = StateHighScoreUpdate,
                              .draw = StateHighScoreDraw,
                              .exit = StateHighScoreExit};

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StateHighScoreEnter(void *args) {
  // TODO
}

void StateHighScoreUpdate(float dt) {
  // TODO
}

void StateHighScoreDraw(void) {
  // TODO
}

void StateHighScoreExit(void) {
  // TODO
}
