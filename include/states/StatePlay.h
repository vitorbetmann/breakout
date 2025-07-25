#ifndef STATE_PLAY_H
#define STATE_PLAY_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Smile.h"

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct {
  int brickCount;
} StatePlayArgs;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void StatePlayEnter(void *args);
void StatePlayUpdate(float dt);
void StatePlayDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern State statePlay;

#endif