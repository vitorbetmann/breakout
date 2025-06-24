// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Util.h"
#include "Paddle.h"
#include "_Constants.h"
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------
#define PADDLES_ORIGIN_Y 64

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
QuadNode **GenerateQuadsPaddles(Texture2D atlas) {
  Vector2 origin = {.x = 0, .y = PADDLES_ORIGIN_Y};
  for (int i = 0; i < PADDLE_SIZES; i++) {
    int tempSkin = 0b0001 << i;
    QuadNode *small = malloc(sizeof(QuadNode));
    *small = (QuadNode){
        .quad = {origin.x, origin.y, PADDLE_SMALL_WIDTH, PADDLE_HEIGHT},
        .skin = tempSkin,
        .next = NULL};

    origin.x += PADDLE_SMALL_WIDTH;
    QuadNode *medium = malloc(sizeof(QuadNode));
    *medium = (QuadNode){
        .quad = {origin.x, origin.y, PADDLE_MEDIUM_WIDTH, PADDLE_HEIGHT},
        .skin = tempSkin,
        .next = NULL};

    origin.x += PADDLE_MEDIUM_WIDTH;
    QuadNode *large = malloc(sizeof(QuadNode));
    *large = (QuadNode){
        .quad = {origin.x, origin.y, PADDLE_LARGE_WIDTH, PADDLE_HEIGHT},
        .skin = tempSkin,
        .next = NULL};

    origin.x = 0;
    origin.y += 16;
    QuadNode *huge = malloc(sizeof(QuadNode));
    *huge = (QuadNode){
        .quad = {origin.x, origin.y, PADDLE_HUGE_WIDTH, PADDLE_HEIGHT},
        .skin = tempSkin,
        .next = NULL};

    // Add all to quads
    AddToQuads(small);
    AddToQuads(medium);
    AddToQuads(large);
    AddToQuads(huge);

    // Shift y for next iteration
    origin.y += 16;
  }

  return quads;
}

void AddToQuads(QuadNode *quadNode) {
  int index = Hash(quadNode->skin, quadNode->quad.width);
  Push(quadNode, index);
}

Rectangle *GetQuad(int skin, int width) {
  QuadNode *temp = malloc(sizeof(QuadNode));
  int index = Hash(skin, width);

  QuadNode *cursor = quads[index];
  while (cursor) {
    if (cursor->skin == skin && cursor->quad.width == width) {
      return &cursor->quad;
    }
    cursor = cursor->next;
  }

  return NULL;
}

int Hash(int skin, int width) {
  int skinIndex = __builtin_ctz(skin);
  int sizeIndex = (width / PADDLE_SMALL_WIDTH) - 1;
  int result = skinIndex * PADDLE_COLORS + sizeIndex;

  return result % ARRAY_SIZE;
}

void Push(QuadNode *quad, int index) {
  QuadNode *cursor = quads[index];
  if (cursor) {
    quad->next = cursor;
  }
  quads[index] = quad;
}

void UnloadQuads(void) {}