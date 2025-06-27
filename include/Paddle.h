#ifndef PADDLE_H
#define PADDLE_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "raylib.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------
#define PADDLE_COLORS 4
#define PADDLE_SIZES 4

#define PADDLE_SMALL_WIDTH 32
#define PADDLE_MEDIUM_WIDTH 64
#define PADDLE_LARGE_WIDTH 96
#define PADDLE_HUGE_WIDTH 128
#define PADDLE_HEIGHT 16

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum {
  P_BLUE = 0b0001,
  P_GREEN = 0b0010,
  P_RED = 0b0100,
  P_PURPLE = 0b1000
} PaddleColor;

typedef struct {
  Rectangle *textureRect;
  Texture2D *texture;
  Vector2 pos;
  float dx;
  int skin;
  int width, height;
  int index;
  Rectangle hitBox;
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
extern Paddle paddle;

#endif