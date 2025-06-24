#ifndef UTILS_H
#define UTILS_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Paddle.h"
#include "raylib.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------
#define PADDLE_ARRAY_SIZE                                                      \
  (PADDLE_SIZES * PADDLE_COLORS) // Best value, but any value works
#define BALL_ARRAY_SIZE 7

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct QuadNodeStruct {
  Rectangle quad;
  int skin;
  struct QuadNodeStruct *next;
} QuadNode;

typedef struct SoundsStruct {
  char *key;
  Sound *value;
  struct SoundsStruct *next;
} SoundNode;

typedef struct AssetNodeStruct {
  char *key;
  void *value;
  struct AssetNodeStruct *next;
} AssetNode;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void *GenerateQuadsPaddles(Texture2D atlas);
void *GenerateQuadsBalls(Texture2D atlas);
Rectangle *GetPaddleQuad(Paddle paddle);

void SoundsAdd(char *key, Sound value);
Sound *SoundsGet(char *key);

void TableAdd(AssetNode *array[], char *key, void *value);
void *TableGet(AssetNode *table[], char *key);

// --------------------------------------------------
// Variables
// --------------------------------------------------
QuadNode paddles[PADDLE_ARRAY_SIZE];
QuadNode balls[BALL_ARRAY_SIZE];
AssetNode *gSounds[26];
AssetNode *gTextures[26];

#endif