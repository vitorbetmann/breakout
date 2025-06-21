// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "../include/smile.h"
#include <string.h>

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
static State *curr_state;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void sm_init(void) { curr_state = NULL; }

State *sm_get_curr_state(void) { return curr_state; }

void sm_change_state(State *state, void *args) {
  if (curr_state && curr_state->exit) {
    curr_state->exit();
  }

  curr_state = state;

  if (curr_state && curr_state->enter) {
    curr_state->enter(args);
  }
}

void sm_update(float dt) {
  if (curr_state && curr_state->update) {
    curr_state->update(dt);
  }
}

void sm_draw(void) {
  if (curr_state && curr_state->draw) {
    curr_state->draw();
  }
}

void sm_shutdown(void) {
  if (curr_state && curr_state->exit) {
    curr_state->exit();
  }
  curr_state = NULL;
}
