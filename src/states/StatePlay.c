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

// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_play_enter(void *args) {
  isPaused = false;

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

    if (CheckCollisionRecs(ball.hitBox, paddle.hitBox)) {
      ball.dy *= -1;
      ball.pos.y = paddle.pos.y - BALL_SIZE;
      PlaySound(*((Sound *)TableGet(gSounds, "paddle hit")));
    }
    CheckBallBrickCollision();
  }
}

bool CheckBallBrickCollision(void) {
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      Brick *temp = bricks[i][j];
      if (!temp->inPlay) {
        continue;
      }
      if (CheckCollisionRecs(ball.hitBox, temp->hitBox)) {
        BrickHit(temp);
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
