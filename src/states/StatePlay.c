// --------------------------------------------------
// Includes
// --------------------------------------------------

#include "_Dependencies.h"

// --------------------------------------------------
// Data types
// --------------------------------------------------
static const char *const PAUSE_TEXT = "PAUSE";

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void CheckPaddleCollision(void);
bool IsBallCollidingWithBrick(void);
void BricksUpdate(float dt);
void PauseTextDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
bool isPaused = false;
extern Font gFont;
extern Ball ball;
extern Paddle paddle;
extern Brick ***bricks;
extern int gScore;
extern int gHealth;
static StatePlayArgs statePlayArgs;
static StateServeArgs stateServeArgs;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StatePlayEnter(void *args) {
  StatePlayArgs *temp = (StatePlayArgs *)args;
  statePlayArgs.brickCount = temp->brickCount;
}

void StatePlayUpdate(float dt) {
  if (IsKeyPressed(KEY_SPACE)) {
    isPaused = !isPaused;

    Sound *s = TableGet(gSounds, "pause");
    PlaySound(*s);
  }

  if (!isPaused) {
    PaddleUpdate(dt);
    BallUpdate(dt);
    BricksUpdate(dt);

    CheckPaddleCollision();
    if (IsBallCollidingWithBrick() && statePlayArgs.brickCount == 0) {
      PlaySound(*((Sound *)TableGet(gSounds, "victory")));
      SM_ChangeStateTo("victory", NULL);
    }

    if (ball.pos.y > VIRTUAL_HEIGHT) {
      gHealth--;
      PlaySound(*(Sound *)TableGet(gSounds, "hurt"));

      if (gHealth == 0) {
        MapUnload();
        SM_ChangeStateTo("game over", NULL);
      } else {
        stateServeArgs.brickCount = statePlayArgs.brickCount;
        SM_ChangeStateTo("serve", &stateServeArgs);
      }
    }
  }
}

void BricksUpdate(float dt) {
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      if (!bricks[i][j]) {
        continue;
      }
      BrickUpdate(bricks[i][j], dt);
    }
  }
}

void CheckPaddleCollision(void) {
  if (CheckCollisionRecs(ball.hitBox, paddle.hitBox)) {
    ball.dy *= -1;
    ball.pos.y = paddle.pos.y - BALL_SIZE;

    // Ball coming from left
    float paddleMidPoint = paddle.pos.x + paddle.width / 2.0;
    if (ball.pos.x < paddleMidPoint && paddle.dx < 0) {
      ball.dx = -(50 + (8 * (paddleMidPoint - ball.pos.x)));
    }
    // Ball coming from right
    else if (ball.pos.x > paddleMidPoint && paddle.dx > 0) {
      ball.dx = 50 + (8 * (ball.pos.x - paddleMidPoint));
    }

    PlaySound(*((Sound *)TableGet(gSounds, "paddle hit")));
  }
}

bool IsBallCollidingWithBrick(void) {
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      Brick *temp = bricks[i][j];
      if (!temp) {
        continue;
      }
      if (temp->inPlay && CheckCollisionRecs(ball.hitBox, temp->hitBox)) {
        gScore += temp->skin * 25 + temp->tier * 200;

        int tempLeft = temp->hitBox.x;
        int tempRight = tempLeft + temp->hitBox.width;
        // Check left edge
        if (ball.pos.x + 2 < tempLeft && ball.dx > 0) {
          ball.pos.x = tempLeft - ball.size;
          ball.dx *= -1;
        }
        // Check right edge
        else if (ball.pos.x + ball.size - 2 > tempRight && ball.dx < 0) {
          ball.pos.x = tempRight;
          ball.dx *= -1;
        }
        // Check top edge
        else if (ball.pos.y < temp->hitBox.y) {
          ball.dy *= -1;
          ball.pos.y = temp->hitBox.y - ball.size;
        }
        // Else, bottom edge it is
        else {
          ball.dy *= -1;
          ball.pos.y = temp->hitBox.y + temp->hitBox.height;
        }

        if (fabs(ball.dy) < 150) {
          ball.dy *= 1.02;
        }

        BrickHit(temp);
        if (!temp->inPlay) {
          statePlayArgs.brickCount--;
        }

        return true;
      }
    }
  }
  return false;
}

void StatePlayDraw(void) {
  PaddleDraw();
  BallDraw();
  BricksDraw();

  if (isPaused) {
    PauseTextDraw();
  }
}

void PauseTextDraw(void) {
  Vector2 textSize = MeasureTextEx(gFont, PAUSE_TEXT, FONT_LARGE, 0);
  Vector2 pos = {(VIRTUAL_WIDTH - textSize.x) / 2.0,
                 (VIRTUAL_HEIGHT - textSize.y) / 2.0};
  DrawTextPro(gFont, PAUSE_TEXT, pos, (Vector2){0, 0}, 0, FONT_LARGE, 0, WHITE);
}
