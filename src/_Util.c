// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Util.h"
#include "_Constants.h"
#include "raylib.h"
#include "stdlib.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------
#define PADDLES_ORIGIN_Y 64
#define PADDLE_TYPES 4

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
QuadNode *GenerateQuadsPaddles(Texture2D atlas) {
  Vector2 origin = {.x = 0, .y = PADDLES_ORIGIN_Y};
  for (int i = 0; i < PADDLE_TYPES; i++) {
    QuadNode small = {
        .quad = {origin.x, origin.y, PADDLE_SMALL_WIDTH, PADDLE_HEIGHT},
        .next = NULL};

    origin.x += PADDLE_SMALL_WIDTH;
    QuadNode medium = {
        .quad = {origin.x, origin.y, PADDLE_MEDIUM_WIDTH, PADDLE_HEIGHT},
        .next = NULL};

    origin.x += PADDLE_MEDIUM_WIDTH;
    QuadNode large = {
        .quad = {origin.x, origin.y, PADDLE_LARGE_WIDTH, PADDLE_HEIGHT},
        .next = NULL};

    origin.x = 0;
    origin.y += 16;
    QuadNode huge = {
        .quad = {origin.x, origin.y, PADDLE_HUGE_WIDTH, PADDLE_HEIGHT},
        .next = NULL};

    // Add all to quads
    AddToQuads(&small);
    AddToQuads(&medium);
    AddToQuads(&large);
    AddToQuads(&huge);

    // Shift y for next iteration
    origin.y += 16;
  }

  return quads;
}

void AddToQuads(QuadNode *quadNode) {
  int index = Hash(&quadNode->quad);
  Push(quadNode, index);
}

Rectangle *GetQuad(int skin, int size) {
  QuadNode *temp = &quads[skin];
  for (int i = 0; i < size; i++) {
    temp = temp->next;
  }
  return &temp->quad;
}

int Hash(Rectangle *quad) {
  if (quad->y >= 64 + 32 * 3) {
    return 3;
  } else if (quad->y >= 64 + 32 * 2) {
    return 2;
  } else if (quad->y >= 64 + 32) {
    return 1;
  } else {
    return 0;
  }
}

void Push(QuadNode *quad, int index) {
  QuadNode *cursor = &quads[index];
  if (cursor) {
    quad->next = cursor;
  }
  quads[index] = *quad;
}