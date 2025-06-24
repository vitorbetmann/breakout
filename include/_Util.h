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
#define ARRAY_SIZE                                                             \
  (PADDLE_SIZES * PADDLE_COLORS) // Best value, but any value works

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct QuadNodeStruct {
  Rectangle quad;
  int skin;
  struct QuadNodeStruct *next;
} QuadNode;

QuadNode *quads[ARRAY_SIZE];

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
QuadNode **GenerateQuadsPaddles(Texture2D atlas);
void AddToQuads(QuadNode *quadNode);
Rectangle *GetQuad(int skin, int size);
int Hash(int skin, int width);
void Push(QuadNode *quad, int index);
void UnloadQuads(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------

#endif