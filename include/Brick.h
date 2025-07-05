#ifndef BRICK_H
#define BRICK_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include <raylib.h>

// --------------------------------------------------
// Other defines
// --------------------------------------------------
#define BRICK_SKINS 5
#define BRICK_TIERS 4
#define BRICK_SPECIAL 1
#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct {
  Rectangle *textureRect;
  Texture2D *texture;
  int skin, tier;
  Rectangle hitBox;
  bool inPlay;
} Brick;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
Brick *NewBrick(int skin, int tier, int posx, int posY);
int GetBrickIndex(Brick *brick);
void BrickHit(Brick *brick);
void BricksDraw(void);
void BrickUnload(Brick *brick);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern Brick ***bricks; // A 2D array of pointers... feels unholy omg
extern int bricksRow, bricksCol;

#endif
