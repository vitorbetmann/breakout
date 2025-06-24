// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StatePlay.h"
#include "Paddle.h"
#include "smile.h"
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
State statePlay = {.id = "play",
                   .enter = state_play_enter,
                   .update = state_play_update,
                   .draw = state_play_draw,
                   .exit = state_play_exit};

// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_play_enter(void *args) { PaddleInit(); }

void state_play_update(float dt) { PaddleUpdate(dt); }

void state_play_draw(void) { PaddleDraw(); }

void state_play_exit(void) {
  // TODO
}
