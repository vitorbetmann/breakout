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
  unsigned int brickCount;
} StateServeArgs;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void state_serve_enter(void *args);
void state_serve_update(float dt);
void state_serve_draw(void);
void state_serve_exit(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern State stateServe;

#endif