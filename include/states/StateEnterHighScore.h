#ifndef STATE_ENTER_HIGH_SCORE_H
#define STATE_ENTER_HIGH_SCORE_H
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
void StateEnterHighScoreEnter(void *args);
void StateEnterHighScoreUpdate(float dt);
void StateEnterHighScoreDraw(void);
void StateEnterHighScoreExit(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern const State stateEnterHighScore;

#endif