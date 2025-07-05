// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Brick.h"
#include "ParticleSystem.h"
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
int colorPallet[5][3] = {
    {99, 155, 255},  // Blue
    {106, 190, 47},  // Green
    {217, 87, 99},   // Red
    {215, 123, 186}, // Purple
    {251, 242, 54},  // Gold
};

Brick ***bricks;
int bricksRow, bricksCol;

// --------------------------------------------------
// Functions
// --------------------------------------------------
Brick *NewBrick(int skin, int tier, int posX, int posY) {
  Brick *newBrick = malloc(sizeof(Brick));
  if (!newBrick) {
    return NULL;
  }
  newBrick->skin = skin;
  newBrick->tier = tier;
  newBrick->inPlay = true;
  newBrick->hitBox = (Rectangle){posX, posY, BRICK_WIDTH, BRICK_HEIGHT};
  newBrick->textureRect = GetBrickQuad(newBrick);
  newBrick->texture = TableGet(gTextures, "main");
  newBrick->particleSystem = NULL;
  return newBrick;
}

int GetBrickIndex(Brick *brick) { return brick->skin * 4 + brick->tier; }

void BrickHit(Brick *brick) {
  PlaySound(*((Sound *)TableGet(gSounds, "brick hit 2")));

  if (brick->tier > 0) {
    if (brick->skin == 0) {
      brick->tier--;
      brick->skin = 4;
    } else {
      brick->skin--;
    }
  } else {
    if (brick->skin == 0) {
      brick->inPlay = false;
    } else {
      brick->skin--;
    }
  }
  brick->textureRect = GetBrickQuad(brick);

  if (!brick->inPlay) {
    PlaySound(*((Sound *)TableGet(gSounds, "brick hit 1")));
  }
}

void BrickUpdate(Brick *brick, float dt) {
  if (!brick->particleSystem) {
    return;
  }
  PS_Update(brick->particleSystem, dt);
}

void BricksDraw(void) {
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      if (bricks[i][j]) {
        BrickDraw(bricks[i][j]);
      }
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

void BrickUnload(Brick *brick) { free(brick); }