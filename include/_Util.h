#ifndef UTILS_H
#define UTILS_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "raylib.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------
#define ARRAY_SIZE 4

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct QuadNodeStruct {
  Rectangle quad;
  struct QuadNodeStruct *next;
} QuadNode;

QuadNode quads[ARRAY_SIZE];

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
QuadNode *GenerateQuadsPaddles(Texture2D atlas);
void AddToQuads(QuadNode *quadNode);
Rectangle *GetQuad(int skin, int size);
int Hash(Rectangle *quad);
void Push(QuadNode *quad, int index);

// --------------------------------------------------
// Variables
// --------------------------------------------------

#endif