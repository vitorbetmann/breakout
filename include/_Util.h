#ifndef UTILS_H
#define UTILS_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Brick.h"
#include "Paddle.h"
#include "raylib.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------
#define PADDLE_ARRAY_SIZE (PADDLE_SIZES * PADDLE_COLORS)
#define BALL_ARRAY_SIZE 7
#define BRICK_ARRAY_SIZE 21 //(BRICK_COLORS * BRICK_TIERS + BRICK_SPECIAL)

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct QuadNodeStruct {
  Rectangle quad;
  int skin;
  struct QuadNodeStruct *next;
} QuadNode;

typedef struct AssetNodeStruct {
  const char *key;
  void *value;
  struct AssetNodeStruct *next;
} AssetNode;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void GenerateAllQuads(Texture2D atlas);

Rectangle *GetPaddleQuad(void);
Rectangle *GetBallQuad(void);
Rectangle *GetBrickQuad(Brick *brick);

void TableAdd(AssetNode *array[], const char *key, void *value);
void *TableGet(AssetNode *table[], const char *key);

// --------------------------------------------------
// Variables
// --------------------------------------------------
QuadNode *paddleQuads[PADDLE_ARRAY_SIZE];
QuadNode *ballQuads[BALL_ARRAY_SIZE];
QuadNode *brickQuads[BRICK_ARRAY_SIZE];

AssetNode *gSounds[26];
AssetNode *gTextures[26];

#endif