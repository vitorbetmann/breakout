#ifndef STATE_SERVE_H
#define STATE_SERVE_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Smile.h"

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct {
  int brickCount;
} StateServeArgs;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void StateServeEnter(void *args);
void StateServeUpdate(float dt);
void StateServeDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern State stateServe;

#endif