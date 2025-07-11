// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateEnterHighScore.h"

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
const State stateEnterHighScore = {.id = "enter high score",
                                   .enter = StateEnterHighScoreEnter,
                                   .update = StateEnterHighScoreUpdate,
                                   .draw = StateEnterHighScoreDraw,
                                   .exit = StateEnterHighScoreExit};

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StateEnterHighScoreEnter(void *args) {
  // TODO
}

void StateEnterHighScoreUpdate(float dt) {
  // TODO
}

void StateEnterHighScoreDraw(void) {
  // TODO
}

void StateEnterHighScoreExit(void) {
  // TODO
}
