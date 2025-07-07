// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Smile.h"
#include "_Dependencies.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
static int healthMax = MAX_HEALTH;
int score;

// --------------------------------------------------
// Variables
// --------------------------------------------------
State stateServe = {.id = "serve",
                    .enter = state_serve_enter,
                    .update = state_serve_update,
                    .draw = state_serve_draw,
                    .exit = NULL};
const char *const PROMPT_TO_PLAY = "Press Enter to serve!";
extern Font gFont;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_serve_enter(void *args) { ball.pos.y = paddle.pos.y - ball.size; }

void state_serve_update(float dt) {
  if (IsKeyPressed(KEY_ENTER)) {
    SM_ChangeState(&statePlay, NULL);
  }

  PaddleUpdate(dt);
  ball.pos.x = paddle.pos.x + (paddle.width - ball.size) / 2.0;
}

void state_serve_draw(void) {

  Vector2 textSize = MeasureTextEx(gFont, PROMPT_TO_PLAY, FONT_MEDIUM, 0);
  Vector2 textPos = {(VIRTUAL_WIDTH - textSize.x) / 2,
                     (VIRTUAL_HEIGHT - textSize.y) / 2.0};
  DrawTextEx(gFont, PROMPT_TO_PLAY, textPos, FONT_MEDIUM, 0, WHITE);
  PaddleDraw();
  BallDraw();
  BricksDraw();
}
