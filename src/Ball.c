// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Ball.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void BallReset(void);
void BallUpdateHitBox(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
Ball ball;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void BallInit(int skin) {
  ball.skin = skin;
  ball.size = BALL_SIZE;
  BallReset();
  ball.index = &ball.skin;
  ball.textureRect = GetBallQuad();
  ball.texture = TableGet(gTextures, "main");
}

void BallReset(void) {
  ball.pos.x = (VIRTUAL_WIDTH - ball.size) / 2.0;
  ball.pos.y = (VIRTUAL_HEIGHT - ball.size) / 2.0;
  ball.dx =
      GetRandomValue(-BALL_MAX_STARTING_SPEED_X, BALL_MAX_STARTING_SPEED_X);
  ball.dy =
      GetRandomValue(BALL_MIN_STARTING_SPEED_Y, BALL_MAX_STARTING_SPEED_Y);
  BallUpdateHitBox();
}

void BallUpdate(float dt) {
  ball.pos.x += ball.dx * dt;
  ball.pos.y += ball.dy * dt;

  if (ball.pos.x < 0 || ball.pos.x + BALL_SIZE > VIRTUAL_WIDTH) {
    ball.dx *= -1;
    ball.pos.x = Clamp(ball.pos.x, 0, VIRTUAL_WIDTH - ball.size);
    PlaySound(*((Sound *)TableGet(gSounds, "wall hit")));
  }

  if (ball.pos.y < 0) {
    ball.dy *= -1;
    ball.pos.y = 0;
    PlaySound(*(Sound *)TableGet(gSounds, "wall hit"));
  }

  BallUpdateHitBox();
}

void BallUpdateHitBox(void) {
  ball.hitBox = (Rectangle){ball.pos.x, ball.pos.y, ball.size, ball.size};
}

void BallDraw(void) {
  Rectangle dest = {ball.pos.x, ball.pos.y, ball.size, ball.size};
  DrawTexturePro(*ball.texture, *ball.textureRect, dest, (Vector2){0, 0}, 0,
                 WHITE);
}
