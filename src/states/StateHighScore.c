// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "states/StateHighScore.h"
#include "HighScoreTable.h"
#include "SaveLoadSystem.h"
#include "StateMachine.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------
// Defines
// --------------------------------------------------
#define HIGH_SCORE_TEXT "HIGH SCORES"
#define RETURN_TEXT "Press ENTER to return to the Main Menu!"

// --------------------------------------------------
// Variables
// --------------------------------------------------

extern Font gFont;

// --------------------------------------------------
// Functions
// --------------------------------------------------

void StateHighScoreEnter(void *args) {
  SLS_Init(NULL, NULL);
  SLS_BeginSaveSession(NULL);
  SLS_SaveNext("betmann");
  SLS_SaveNext("1000");
  SLS_SaveNext("jubs");
  SLS_SaveNext("5000");
  SLS_SaveNext("aloalo");
  SLS_SaveNext("9000");
  SLS_EndSaveSession();
}

void StateHighScoreUpdate(float dt) {

  if (IsKeyPressed(KEY_ENTER)) {
    PlaySound(*(Sound *)TableGet(gSounds, "wall hit"));
    SM_ChangeStateTo("start", NULL);
  }
}

void StateHighScoreDraw(void) {

  int fontSize = FONT_LARGE;
  int spacing = 0;
  char *text = HIGH_SCORE_TEXT;
  Vector2 textSize = MeasureTextEx(gFont, text, fontSize, spacing);
  Vector2 textPos = {(VIRTUAL_WIDTH - textSize.x) / 2.0, 20};
  DrawTextEx(gFont, text, textPos, fontSize, spacing, WHITE);

  fontSize = FONT_MEDIUM;
  char bufferScore[32];
  char bufferRank[4];
  for (int i = 0; i < MAX_SCORES; i++) {
    PlayerData temp = GetPlayerData(i);

    const char *name = temp.name;
    char *scoreStr = BLANK_NAME;

    if (strcmp(temp.name, BLANK_NAME) != 0) {
      snprintf(bufferScore, sizeof(bufferScore), "%d", temp.score);
      scoreStr = bufferScore;
    }

    snprintf(bufferRank, sizeof(bufferRank), "%d.", i + 1);
    Vector2 textWidth = MeasureTextEx(gFont, bufferRank, fontSize, spacing);
    textPos.x = VIRTUAL_WIDTH / 4.0 - textWidth.x / 2.0;
    textPos.y = 60 + i * 13;
    DrawTextEx(gFont, bufferRank, textPos, fontSize, spacing, WHITE);

    textPos.x = VIRTUAL_WIDTH / 2.0 - 38;
    DrawTextEx(gFont, name, textPos, fontSize, spacing, WHITE);

    textWidth = MeasureTextEx(gFont, scoreStr, fontSize, spacing);
    textPos.x = 3 * VIRTUAL_WIDTH / 4.0 - textWidth.x;
    DrawTextEx(gFont, scoreStr, textPos, fontSize, spacing, WHITE);
  }

  fontSize = FONT_SMALL;
  text = RETURN_TEXT;
  textSize = MeasureTextEx(gFont, text, fontSize, spacing);
  textPos.x = (VIRTUAL_WIDTH - textSize.x) / 2.0;
  textPos.y = VIRTUAL_HEIGHT - 18;
  DrawTextEx(gFont, text, textPos, fontSize, spacing, WHITE);
}

void StateHighScoreExit(void) { SLS_Shutdown(); }