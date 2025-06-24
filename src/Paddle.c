// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "Paddle.h"
#include "_Constants.h"
#include "_Util.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------

// --------------------------------------------------
// Variables
// --------------------------------------------------
static Paddle paddle;
extern QuadNode gFrames;
extern Texture2D gMain;

// --------------------------------------------------
// Functions
// --------------------------------------------------
void print_hashtable(void) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("Index: %d\n", i);
    for (QuadNode *j = quads[i]; j != NULL; j = j->next) {
      printf("\tquad - x: %d, y: %d\n", (int)j->quad.x, (int)j->quad.y);
    }
    puts("");
  }
}

void PaddleInit(void) {
  paddle.skin = S_BLUE;
  paddle.width = PADDLE_MEDIUM_WIDTH;
  paddle.height = PADDLE_HEIGHT;
  paddle.pos.x = (VIRTUAL_WIDTH - paddle.width) / 2.0;
  paddle.pos.y = VIRTUAL_HEIGHT - STARTING_Y;
  paddle.textureRect = GetQuad(paddle.skin, paddle.width);

  // print_hashtable();
}

void PaddleUpdate(float dt) {
  paddle.dx = 0;
  if (IsKeyDown(KEY_LEFT)) {
    paddle.dx = -PADDLE_SPEED;
  } else if (IsKeyDown(KEY_RIGHT)) {
    paddle.dx = PADDLE_SPEED;
  }

  paddle.pos.x += paddle.dx * dt;
  paddle.pos.x = Clamp(paddle.pos.x, 0, VIRTUAL_WIDTH - paddle.width);
}

void PaddleDraw() {
  Rectangle dest = {paddle.pos.x, paddle.pos.y, paddle.width, paddle.height};
  DrawTexturePro(gMain, *paddle.textureRect, dest, (Vector2){0, 0}, 0, WHITE);
}