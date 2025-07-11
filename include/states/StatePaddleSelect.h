#ifndef STATE_PADDLE_SELECT_H
#define STATE_PADDLE_SELECT_H
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
void StatePaddleSelectEnter(void *args);
void StatePaddleSelectUpdate(float dt);
void StatePaddleSelectDraw(void);
void StatePaddleSelectExit(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern const State statePaddleSelect;

#endif