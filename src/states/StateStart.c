// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateStart.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"
#include "smile.h"
#include "states/StatePlay.h"

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
static int highlighted = START;

State stateStart = {.id = "start",
                    .enter = NULL,
                    .update = state_start_update,
                    .draw = state_start_draw,
                    .exit = NULL};

extern Font gFont;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_start_update(float dt) {
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
    highlighted++;
    highlighted %= 2;
    PlaySound(*((Sound *)TableGet(gSounds, "paddle hit")));
  }

  if (IsKeyPressed(KEY_ENTER)) {
    switch ((Options)highlighted) {
    case START:
      sm_change_state(&statePlay, NULL);
      break;
    case HIGH_SCORE:
      // TODO handle this later
      break;
    }
  }
}

void state_start_draw(void) {
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
