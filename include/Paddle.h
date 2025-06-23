#ifndef PADDLE_H
#define PADDLE_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Constants.h"
#include "raylib.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum { S_BLUE, S_GREEN, S_RED, S_PURPLE } Skin;

typedef enum {
  SMALL = PADDLE_SMALL_WIDTH,
  MEDIUM = PADDLE_MEDIUM_WIDTH,
  LARGE = PADDLE_LARGE_WIDTH,
  HUGE = PADDLE_HUGE_WIDTH
} Size;

typedef struct {
  Rectangle *textureRect;
  Vector2 pos;
  float dx;
  int skin;
  int width, height;
} Paddle;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void PaddleInit(void);
void PaddleUpdate(float dt);
void PaddleDraw(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------

#endif