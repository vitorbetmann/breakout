// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StatePlay.h"
#include "Ball.h"
#include "Brick.h"
#include "LevelMaker.h"
#include "Paddle.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"
#include "smile.h"
#include <math.h>
#include <stdlib.h>

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------
static const char *const PAUSE_TEXT = "PAUSE";

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void CheckPaddleCollision(void);
bool CheckBallBrickCollision(void);
void PauseTextDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
State statePlay = {.id = "play",
                   .enter = state_play_enter,
                   .update = state_play_update,
                   .draw = state_play_draw,
                   .exit = state_play_exit};

static bool isPaused;
extern Font gFont;
extern Ball ball;
extern Paddle paddle;
extern Brick ***bricks;
static int score;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_play_enter(void *args) {
  isPaused = false;
  score = 0;

  PaddleInit();
  BallInit(GetRandomValue(0, 6));
  CreateMap();
}

void state_play_update(float dt) {
  if (IsKeyPressed(KEY_SPACE)) {
    isPaused = !isPaused;

    Sound *s = TableGet(gSounds, "pause");
    PlaySound(*s);
  }

  if (!isPaused) {
    PaddleUpdate(dt);
    BallUpdate(dt);

    CheckPaddleCollision();
    CheckBallBrickCollision();
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

bool CheckBallBrickCollision(void) {
  bool hasCollided = false;
  for (int i = 0; i < bricksRow && !hasCollided; i++) {
    for (int j = 0; j < bricksCol && !hasCollided; j++) {
      Brick *temp = bricks[i][j];
      if (temp->inPlay && CheckCollisionRecs(ball.hitBox, temp->hitBox)) {
        score += 10;

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

        hasCollided = true;
      }
    }
  }
  return false;
}

void state_play_draw(void) {
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

void state_play_exit(void) {
  // TODO
}
