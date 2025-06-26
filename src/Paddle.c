// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Paddle.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
int SetIndex(int skin, int width);
void PaddleUpdateHitBox(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
Paddle paddle;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void PaddleInit(void) {
  paddle.skin = P_BLUE;
  paddle.width = PADDLE_MEDIUM_WIDTH;
  paddle.height = PADDLE_HEIGHT;
  paddle.pos.x = (VIRTUAL_WIDTH - paddle.width) / 2.0;
  paddle.pos.y = VIRTUAL_HEIGHT - STARTING_Y;
  paddle.index = SetIndex(paddle.skin, paddle.width);
  paddle.textureRect = GetPaddleQuad();
  paddle.texture = TableGet(gTextures, "main");
  PaddleUpdateHitBox();
}

int SetIndex(int skin, int width) {
  int skinIndex = __builtin_ctz(skin);
  int sizeIndex = (width / PADDLE_SMALL_WIDTH) - 1;
  int result = skinIndex * PADDLE_COLORS + sizeIndex;

  return result;
}

void PaddleUpdate(float dt) {
  paddle.dx = 0;
  if (IsKeyDown(KEY_LEFT)) {
    paddle.dx = -PADDLE_SPEED;
  } else if (IsKeyDown(KEY_RIGHT)) {
    paddle.dx = PADDLE_SPEED;
  }

  paddle.pos.x += paddle.dx * dt;
  paddle.pos.x = Clamp(paddle.pos.x, 0, VIRTUAL_WIDTH - paddle.width);
  PaddleUpdateHitBox();
}

void PaddleUpdateHitBox(void) {
  paddle.hitBox =
      (Rectangle){paddle.pos.x, paddle.pos.y, paddle.width, paddle.height};
}

void PaddleDraw() {
  Rectangle dest = {paddle.pos.x, paddle.pos.y, paddle.width, paddle.height};
  DrawTexturePro(*paddle.texture, *paddle.textureRect, dest, (Vector2){0, 0}, 0,
                 WHITE);
}