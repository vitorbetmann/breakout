#ifndef STATE_TWO_H
#define STATE_TWO_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "../../include/smile.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void state_two_enter(void *args);
void state_two_update(float dt);
void state_two_draw(void);
void state_two_exit(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern State state_two;

#endif