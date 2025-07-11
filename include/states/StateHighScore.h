#ifndef STATE_HIGH_SCORE_H
#define STATE_HIGH_SCORE_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Smile.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void StateHighScoreEnter(void *args);
void StateHighScoreUpdate(float dt);
void StateHighScoreDraw(void);
void StateHighScoreExit(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern const State stateHighScore;

#endif