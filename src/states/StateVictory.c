// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Dependencies.h"

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern unsigned int currLevel;
extern Font gFont;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void StateVictoryUpdate(float dt) {
  if (IsKeyPressed(KEY_ENTER)) {
    currLevel++;
    SM_ChangeStateTo("init", NULL);
  }
}

void StateVictoryDraw(void) {

  // Draw "Level {number} Complete"
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Level %d Complete!", currLevel);
  Vector2 textSize = MeasureTextEx(gFont, buffer, FONT_LARGE, 0);
  Vector2 position = {(VIRTUAL_WIDTH - textSize.x) / 2.0f,
                      (VIRTUAL_HEIGHT - textSize.y) / 2.0f - 30};
  DrawTextEx(gFont, buffer, position, FONT_LARGE, 0, WHITE);

  // Draw "Press Enter to Continue"
  char *continueText = "Press Enter to Continue";
  textSize = MeasureTextEx(gFont, continueText, FONT_MEDIUM, 0);
  position.x = (VIRTUAL_WIDTH - textSize.x) / 2.0f;
  position.y = (VIRTUAL_HEIGHT - textSize.y) / 2.0f;
  DrawTextEx(gFont, continueText, position, FONT_MEDIUM, 0, WHITE);
}
