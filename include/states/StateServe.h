#ifndef STATE_SERVE_H
#define STATE_SERVE_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "smile.h"

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