// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Smile.h"
#include "_Constants.h"
#include "_Dependencies.h"
#include "raylib.h"
#include "states/StateGameInit.h"
#include <stdio.h>

// --------------------------------------------------
// Variables
// --------------------------------------------------
State stateGameOver = {.id = "game over",
                       .enter = NULL,
                       .update = state_game_over_update,
                       .draw = state_game_over_draw,
                       .exit = NULL};
extern Font gFont;
extern int gScore;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void state_game_over_update(float dt) {
  if (IsKeyPressed(KEY_ENTER)) {
    SM_ChangeState(&stateGameInit, NULL);
  }
}

void state_game_over_draw(void) {
  Vector2 textSize = MeasureTextEx(gFont, GAME_OVER_TEXT, FONT_LARGE, 0);
  Vector2 textPos = {(VIRTUAL_WIDTH - textSize.x) / 2.0, VIRTUAL_HEIGHT / 3.0};
  DrawTextEx(gFont, GAME_OVER_TEXT, textPos, FONT_LARGE, 0, WHITE);

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%s %04d", FINAL_SCORE_TEXT, gScore);
  textSize = MeasureTextEx(gFont, buffer, FONT_MEDIUM, 0);
  textPos.x = (VIRTUAL_WIDTH - textSize.x) / 2.0;
  textPos.y = VIRTUAL_HEIGHT / 2.0;
  DrawTextEx(gFont, buffer, textPos, FONT_MEDIUM, 0, WHITE);

  textSize = MeasureTextEx(gFont, CONTINUE_TEXT, FONT_MEDIUM, 0);
  textPos.x = (VIRTUAL_WIDTH - textSize.x) / 2.0;
  textPos.y = VIRTUAL_HEIGHT - VIRTUAL_HEIGHT / 4.0;
  DrawTextEx(gFont, CONTINUE_TEXT, textPos, FONT_MEDIUM, 0, WHITE);
}
