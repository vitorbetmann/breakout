// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Brick.h"
#include "_Constants.h"
#include "math.h"
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum { NONE, SIGLE_PYRAMID, MULTI_PYRAMID } GlobalPattern;
typedef enum {
  SOLID,
  ALTERNATE,
  SKIPE,
  NO_BLOCKS,
} PerRowPattern;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------

// --------------------------------------------------
// Variables
// --------------------------------------------------

// --------------------------------------------------
// Functions
// --------------------------------------------------
void MapCreate(int level) {
  bricksRow = GetRandomValue(BRICKS_ROW_MIN, BRICKS_ROW_MAX);
  bricksCol = GetRandomValue(BRICKS_COL_MIN, BRICKS_COL_MAX);
  bricksCol = bricksCol % 2 == 0 ? bricksCol + 1 : bricksCol;

  printf("row: %d, col: %d\n", bricksRow, bricksCol);

  int highestTier = (int)fmin(3, (float)level / TIER_THRESHOLD);
  int highestColor = (int)fmin(4, level % 4 + 3);

  bricks = malloc(bricksRow * sizeof(Brick));
  int startingX = (VIRTUAL_WIDTH - bricksCol * BRICK_WIDTH) / 2.0;
  Vector2 origin = {startingX, BRICK_HEIGHT};

  for (int i = 0; i < bricksRow; i++) {

    bool skip = GetRandomValue(0, 1) == 0 ? true : false;
    bool alternate = GetRandomValue(0, 1) == 0 ? true : false;

    int color1 = GetRandomValue(0, highestColor);
    int color2 = GetRandomValue(0, highestColor);
    int tier1 = GetRandomValue(0, highestTier);
    int tier2 = GetRandomValue(0, highestTier);

    bool skipFlag = GetRandomValue(0, 1) == 0 ? true : false;
    bool alternateFlag = GetRandomValue(0, 1) == 0 ? true : false;

    int solidColor = GetRandomValue(0, highestColor);
    int solidTier = GetRandomValue(0, highestTier);

    bricks[i] = malloc(bricksCol * sizeof(Brick));

    for (int j = 0; j < bricksCol; j++) {
      int tempSkin, tempTier;
      if (alternate && alternateFlag) {
        tempSkin = color1;
        tempTier = tier1;
      } else {
        tempSkin = color2;
        tempTier = tier2;
      }
      alternateFlag = !alternateFlag;

      if (!alternate) {
        tempSkin = solidColor;
        tempTier = solidTier;
      }

      bricks[i][j] = NewBrick(tempSkin, tempTier, origin.x, origin.y);

      if (skip && skipFlag) {
        bricks[i][j]->inPlay = false;
      }
      skipFlag = !skipFlag;

      origin.x += BRICK_WIDTH;
    }
    origin.x = startingX;
    origin.y += BRICK_HEIGHT;
  }
}

void MapUnload(void) {
  for (int i = 0; i < bricksRow; i++) {
    for (int j = 0; j < bricksCol; j++) {
      BrickUnload(bricks[i][j]);
    }
    free(bricks[i]);
  }
  free(bricks);
  bricks = NULL;
}
