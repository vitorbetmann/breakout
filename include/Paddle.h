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
#define PADDLE_SIZES 4
#define PADDLE_COLORS 4

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum {
  S_BLUE = 0b0001,
  S_GREEN = 0b0010,
  S_RED = 0b0100,
  S_PURPLE = 0b1000
} Skin;

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