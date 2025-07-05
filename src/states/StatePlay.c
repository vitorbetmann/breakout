// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "LevelMaker.h"
#include "_Dependencies.h"

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
                   .enter = NULL,
                   .update = state_play_update,
                   .draw = state_play_draw,
                   .exit = NULL};

bool isPaused = false;
extern Font gFont;
extern Ball ball;
extern Paddle paddle;
extern Brick ***bricks;
extern int gScore;
extern int gHealth;

// --------------------------------------------------
// Functions
// --------------------------------------------------
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

    if (ball.pos.y > VIRTUAL_HEIGHT) {
      gHealth--;
      PlaySound(*(Sound *)TableGet(gSounds, "hurt"));

      if (gHealth == 0) {
        MapUnload();
        sm_change_state(&stateGameOver, NULL);
      } else {
        sm_change_state(&stateServe, NULL);
      }
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

bool CheckBallBrickCollision(void) {
  bool hasCollided = false;
  for (int i = 0; i < bricksRow && !hasCollided; i++) {
    for (int j = 0; j < bricksCol && !hasCollided; j++) {
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
