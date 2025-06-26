// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Brick.h"
#include "_Util.h"
#include "raylib.h"
#include "stdlib.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void BrickDraw(Brick *brick);

// --------------------------------------------------
// Variables
// --------------------------------------------------
Brick ***bricks;
int bricksRow, bricksCol;

// --------------------------------------------------
// Functions
// --------------------------------------------------
Brick *NewBrick(int posX, int posY) {
  Brick *newBrick = malloc(sizeof(Brick));
  newBrick->skin = 0;
  newBrick->tier = 0;
  newBrick->index = newBrick->skin * 4 + newBrick->tier;
  newBrick->inPlay = true;
  newBrick->hitBox = (Rectangle){posX, posY, BRICK_WIDTH, BRICK_HEIGHT};
  newBrick->textureRect = GetBrickQuad(newBrick);
  newBrick->texture = TableGet(gTextures, "main");
  return newBrick;
}

void BrickHit(Brick *brick) {
  brick->inPlay = false;
  PlaySound(*((Sound *)TableGet(gSounds, "brick hit 2")));
}

void BricksDraw(void) {
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      BrickDraw(bricks[i][j]);
    }
  }
}

void BrickDraw(Brick *brick) {
  if (!brick->inPlay) {
    return;
  }
  DrawTexturePro(*brick->texture, *brick->textureRect, brick->hitBox,
                 (Vector2){0, 0}, 0, WHITE);
}