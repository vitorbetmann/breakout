// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Brick.h"
#include "_Constants.h"
#include "raylib.h"
#include "stdio.h"
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

// --------------------------------------------------
// Variables
// --------------------------------------------------

// --------------------------------------------------
// Functions
// --------------------------------------------------
void MapCreate(void) {
  bricksRow = GetRandomValue(BRICKS_ROW_MIN, BRICKS_ROW_MAX);
  bricksCol = GetRandomValue(BRICKS_COL_MIN, BRICKS_COL_MAX);

  bricks = malloc(bricksRow * sizeof(Brick));
  int startingX = (VIRTUAL_WIDTH - bricksCol * 32) / 2.0;
  Vector2 origin = {startingX, BRICK_HEIGHT};
  for (int i = 0; i < bricksRow; i++) {
    bricks[i] = malloc(bricksCol * sizeof(Brick));
    for (int j = 0; j < bricksCol; j++) {
      bricks[i][j] = NewBrick(origin.x, origin.y);
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
