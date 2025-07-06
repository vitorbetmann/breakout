#ifndef BRICK_H
#define BRICK_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "ParticleSystem.h"
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
typedef enum {
  SKIN_BLUE,
  SKIN_GREEN,
  SKIN_RED,
  SKIN_PURPLE,
  SKIN_GOLD
} BrickSkin;

typedef struct {
  Rectangle *textureRect;
  Texture2D *texture;
  int skin, tier;
  Rectangle hitBox;
  bool inPlay;
  ParticleSystem *particleSystem;
} Brick;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
Brick *NewBrick(int skin, int tier, int posx, int posY);
int GetBrickIndex(Brick *brick);
void BrickHit(Brick *brick);
void BrickUpdate(Brick *brick, float dt);
void BricksDraw(void);
void BrickUnload(Brick *brick);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern Brick ***bricks; // A 2D array of pointers... feels unholy omg
extern int bricksRow, bricksCol;

#endif
