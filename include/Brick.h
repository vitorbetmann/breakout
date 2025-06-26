#ifndef BRICK_H
#define BRICK_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Constants.h"
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
  int index;
} Brick;

typedef struct BrickNodeStruct {
  struct BrickNodeStruct *next;
  Brick *brick;
} BrickNode;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
Brick *NewBrick(int posx, int posY);
void BrickHit(Brick *brick);
void BricksDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern Brick ***bricks; // A 2D array of pointers... feels unholy omg
extern int bricksRow, bricksCol;

#endif
