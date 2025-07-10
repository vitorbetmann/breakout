#ifndef BALL_H
#define BALL_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "raylib.h"

// --------------------------------------------------
// Other defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef struct {
  int skin;
  int size;
  Vector2 pos;
  float dx, dy;
  int *index;
  Rectangle *textureRect;
  Texture2D *texture;
  Rectangle hitBox;
} Ball;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void BallInit(int skin);
void BallReset(void);
void BallUpdate(float dt);
void BallDraw(void);
bool HasBallCollided(Rectangle target);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern Ball ball;

#endif