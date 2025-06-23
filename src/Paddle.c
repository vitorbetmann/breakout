// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Paddle.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------
#define STARTING_Y 32

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------

// --------------------------------------------------
// Variables
// --------------------------------------------------
static Paddle paddle;
extern QuadNode gFrames;
extern Texture2D gMain;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void PaddleInit(void) {
  paddle.skin = S_BLUE;
  paddle.width = MEDIUM;
  paddle.height = PADDLE_HEIGHT;
  paddle.pos.x = (VIRTUAL_WIDTH - paddle.width) / 2.0;
  paddle.pos.y = VIRTUAL_HEIGHT - STARTING_Y;
  paddle.textureRect = GetQuad(paddle.skin, paddle.width);
}

void PaddleUpdate(float dt) {
  // TODO handle input
}

void PaddleDraw() {
  Rectangle dest = {paddle.pos.x, paddle.pos.y, paddle.width, paddle.height};
  DrawTexturePro(gMain, *paddle.textureRect, dest, (Vector2){0, 0}, 0, WHITE);
}