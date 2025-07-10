#ifndef STATE_VICTORY_H
#define STATE_VICTORY_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Smile.h"

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void StateVictoryEnter(void *args);
void StateVictoryUpdate(float dt);
void StateVictoryDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern const State stateVictory;

#endif