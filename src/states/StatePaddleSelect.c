// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StatePaddleSelect.h"

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
const State statePaddleSelect = {.id = "paddle select",
                                 .enter = StatePaddleSelectEnter,
                                 .update = StatePaddleSelectUpdate,
                                 .draw = StatePaddleSelectDraw,
                                 .exit = StatePaddleSelectExit};

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StatePaddleSelectEnter(void *args) {
  // TODO
}

void StatePaddleSelectUpdate(float dt) {
  // TODO
}

void StatePaddleSelectDraw(void) {
  // TODO
}

void StatePaddleSelectExit(void) {
  // TODO
}
