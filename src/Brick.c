// TODO raylib has a LERP function

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Brick.h"
#include "ParticleSystem.h"
#include "_Util.h"
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------
#define COLOR_BLUE {99, 155, 255}
#define COLOR_GREEN {106, 190, 47}
#define COLOR_RED {217, 87, 99}
#define COLOR_PURPLE {215, 123, 186}
#define COLOR_GOLD {251, 242, 54}

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

  return newBrick;
}

int GetBrickIndex(Brick *brick) { return brick->skin * 4 + brick->tier; }

void BrickHit(Brick *brick) {
  PlaySound(*((Sound *)TableGet(gSounds, "brick hit 2")));

  Texture2D *texture = TableGet(gTextures, "particle");
  brick->particleSystem =
      newParticleSystem(texture, 64,
                        (Vector2){brick->hitBox.x + BRICK_WIDTH / 2.0,
                                  brick->hitBox.y + BRICK_HEIGHT / 2.0},
                        500, 1000, -10, 0, 15, 80, NORMAL, 10, 10);

  Color color1, color2;
  switch (brick->skin) {
  case SKIN_BLUE:
    color1 = color2 = (Color)COLOR_BLUE;
    break;
  case SKIN_GREEN:
    color1 = color2 = (Color)COLOR_GREEN;
    break;
  case SKIN_RED:
    color1 = color2 = (Color)COLOR_RED;
    break;
  case SKIN_PURPLE:
    color1 = color2 = (Color)COLOR_PURPLE;
    break;
  case SKIN_GOLD:
    color1 = color2 = (Color)COLOR_GOLD;
    break;
  }
  color1.a = 55 * (brick->tier + 1);
  color2.a = 0;

  PS_SetColors(brick->particleSystem, color1, color2);
  PS_Emit(brick->particleSystem);

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

  if (brick->inPlay) {
    DrawTexturePro(*brick->texture, *brick->textureRect, brick->hitBox,
                   (Vector2){0, 0}, 0, WHITE);
  }

  if (brick->particleSystem) {
    PS_Draw(brick->particleSystem);
  }
}

void BrickUnload(Brick *brick) {
  // TODO improve this
  free(brick);
}