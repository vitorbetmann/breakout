// --------------------------------------------------
// Includes
// --------------------------------------------------
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
extern Font gFont;
static unsigned int brickCount;
const char *const PROMPT_TO_PLAY = "Press Enter to serve!";
// --------------------------------------------------
// Functions
// --------------------------------------------------
void StateServeEnter(void *args) {
  BallReset();
  ball.pos.y = paddle.pos.y - ball.size;

  StateServeArgs *temp = (StateServeArgs *)args;
  brickCount = temp->brickCount;
}

void StateServeUpdate(float dt) {
  if (IsKeyPressed(KEY_ENTER)) {
    StatePlayArgs statePlayArgs = {.brickCount = brickCount};
    SM_ChangeStateTo("play", &statePlayArgs);
  }

  PaddleUpdate(dt);
  ball.pos.x = paddle.pos.x + (paddle.width - ball.size) / 2.0;
}

void StateServeDraw(void) {

  // Draw "Level {number}"
  char buffer[16];
  snprintf(buffer, sizeof(buffer), "Level %d", currLevel);
  Vector2 textSize = MeasureTextEx(gFont, buffer, FONT_LARGE, 0);
  Vector2 textPos = {(VIRTUAL_WIDTH - textSize.x) / 2.0f,
                     (VIRTUAL_HEIGHT - textSize.y) / 2.0f - 30};
  DrawTextEx(gFont, buffer, textPos, FONT_LARGE, 0, WHITE);

  // Draw "Press Enter to Serve"
  textSize = MeasureTextEx(gFont, PROMPT_TO_PLAY, FONT_MEDIUM, 0);
  textPos.x = (VIRTUAL_WIDTH - textSize.x) / 2;
  textPos.y = (VIRTUAL_HEIGHT - textSize.y) / 2.0;
  DrawTextEx(gFont, PROMPT_TO_PLAY, textPos, FONT_MEDIUM, 0, WHITE);

  PaddleDraw();
  BallDraw();
  BricksDraw();
}
