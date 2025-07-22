// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Dependencies.h"

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum {
  START,
  HIGH_SCORE,
} Options;

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern Font gFont;
static int highlighted = START;
static StateServeArgs stateServeArgs;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StateStartUpdate(float dt) {
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
    highlighted++;
    highlighted %= 2;

    Sound *s = TableGet(gSounds, "paddle hit");
    PlaySound(*s);
  }

  if (IsKeyPressed(KEY_ENTER)) {
    switch ((Options)highlighted) {
    case START:
      PaddleInit();
      BallInit(GetRandomValue(0, 6));
      SM_ChangeStateTo("init", NULL);
      break;
    case HIGH_SCORE:
      SM_ChangeStateTo("high score", NULL);
      break;
    }
  }
}

void StateStartDraw(void) {
  Vector2 textLength = MeasureTextEx(gFont, GAME_TITLE, FONT_LARGE, 0);
  Vector2 textPos = {0};
  textPos.x = (VIRTUAL_WIDTH - textLength.x) / 2.0;
  textPos.y = VIRTUAL_HEIGHT / 3.0;
  DrawTextEx(gFont, GAME_TITLE, textPos, FONT_LARGE, 0, WHITE);

  Color highlightColor = {103, 255, 255, 255};
  Color startColor = WHITE, highScoresColor = WHITE;

  switch (highlighted) {
  case 0:
    startColor = highlightColor;
    break;
  case 1:
    highScoresColor = highlightColor;
    break;
  }

  textLength = MeasureTextEx(gFont, OPTION_START, FONT_MEDIUM, 0);
  textPos.x = (VIRTUAL_WIDTH - textLength.x) / 2.0;
  textPos.y = VIRTUAL_HEIGHT / 2.0 + 70;
  DrawTextEx(gFont, OPTION_START, textPos, FONT_MEDIUM, 0, startColor);

  textLength = MeasureTextEx(gFont, OPTION_HIGH_SCORES, FONT_MEDIUM, 0);
  textPos.x = (VIRTUAL_WIDTH - textLength.x) / 2.0;
  textPos.y = VIRTUAL_HEIGHT / 2.0 + 90;
  DrawTextEx(gFont, OPTION_HIGH_SCORES, textPos, FONT_MEDIUM, 0,
             highScoresColor);
}
