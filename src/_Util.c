// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Util.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "_Constants.h"
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include <string.h>

// --------------------------------------------------
// Defines
// --------------------------------------------------
#define PADDLES_ORIGIN_Y 64

#define BALLS_ORIGIN_X 96
#define BALLS_ORIGIN_Y 48
#define BALLS_AMOUNT_ROW_1 4
#define BALLS_AMOUNT_ROW_2 3

// --------------------------------------------------
// Data types
// --------------------------------------------------
#define ROWS 4
#define COLS 6

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
// void GenerateQuads(Texture2D atlas);
void GenerateBrickQuads(Texture2D atlas);
void GeneratePaddleQuads(Texture2D atlas);
void GenerateBallQuads(Texture2D atlas);

void Slice(QuadNode *src[], QuadNode *dest[], int start, int end);

int Hash(const char *key);

// --------------------------------------------------
// Variables
// --------------------------------------------------

// --------------------------------------------------
// Functions
// --------------------------------------------------
void GenerateAllQuads(Texture2D atlas) {
  GeneratePaddleQuads(atlas);
  GenerateBallQuads(atlas);
  GenerateBrickQuads(atlas);
}

void GeneratePaddleQuads(Texture2D atlas) {
  Vector2 origin = {.x = 0, .y = PADDLES_ORIGIN_Y};
  int counter = 0;

  for (int i = 0; i < PADDLE_SIZES; i++) {
    int tempSkin = 0b0001 << i;

    QuadNode *small = malloc(sizeof(QuadNode));
    small->quad.x = origin.x;
    small->quad.y = origin.y;
    small->quad.width = PADDLE_SMALL_WIDTH;
    small->quad.height = PADDLE_HEIGHT;
    small->skin = tempSkin;
    small->next = NULL;

    origin.x += PADDLE_SMALL_WIDTH;
    QuadNode *medium = malloc(sizeof(QuadNode));
    medium->quad.x = origin.x;
    medium->quad.y = origin.y;
    medium->quad.width = PADDLE_MEDIUM_WIDTH;
    medium->quad.height = PADDLE_HEIGHT;
    medium->skin = tempSkin;
    medium->next = NULL;

    origin.x += PADDLE_MEDIUM_WIDTH;
    QuadNode *large = malloc(sizeof(QuadNode));
    large->quad.x = origin.x;
    large->quad.y = origin.y;
    large->quad.width = PADDLE_LARGE_WIDTH;
    large->quad.height = PADDLE_HEIGHT;
    large->skin = tempSkin;
    large->next = NULL;

    origin.x = 0;
    origin.y += 16;
    QuadNode *huge = malloc(sizeof(QuadNode));
    huge->quad.x = origin.x;
    huge->quad.y = origin.y;
    huge->quad.width = PADDLE_HUGE_WIDTH;
    huge->quad.height = PADDLE_HEIGHT;
    huge->skin = tempSkin;
    huge->next = NULL;

    // Add all to paddles array
    paddleQuads[counter++] = small;
    paddleQuads[counter++] = medium;
    paddleQuads[counter++] = large;
    paddleQuads[counter++] = huge;

    // Shift y for next iteration
    origin.y += 16;
  }
}

void GenerateBallQuads(Texture2D atlas) {
  Vector2 origin = {.x = BALLS_ORIGIN_X, .y = BALLS_ORIGIN_Y};

  for (int i = 0; i < BALLS_AMOUNT_ROW_1; i++) {
    QuadNode *ball = malloc(sizeof(QuadNode));
    ball->quad.x = origin.x;
    ball->quad.y = origin.y;
    ball->quad.width = BALL_SIZE;
    ball->quad.height = BALL_SIZE;
    ball->next = NULL;
    ball->skin = i;

    ballQuads[i] = ball;
    origin.x += BALL_SIZE;
  }

  origin.x = 96;
  origin.y = 56;

  for (int i = 0; i < BALLS_AMOUNT_ROW_2; i++) {
    QuadNode *ball = malloc(sizeof(QuadNode));
    ball->quad.x = origin.x;
    ball->quad.y = origin.y;
    ball->quad.width = BALL_SIZE;
    ball->quad.height = BALL_SIZE;
    ball->next = NULL;
    ball->skin = i + BALLS_AMOUNT_ROW_1;

    ballQuads[i + BALLS_AMOUNT_ROW_1] = ball;
    origin.x += BALL_SIZE;
  }
}

void GenerateBrickQuads(Texture2D atlas) {
  int counter = 0, skin = 0;
  Vector2 origin = {0, 0};
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      QuadNode *temp = malloc(sizeof(QuadNode));
      temp->quad.x = origin.x;
      temp->quad.y = origin.y;
      temp->quad.width = BRICK_WIDTH;
      temp->quad.height = BRICK_HEIGHT;
      temp->skin = skin;
      temp->next = NULL;
      brickQuads[counter] = temp;

      counter++;
      if (counter == BRICK_ARRAY_SIZE) {
        break;
      }
      skin++;
      skin %= BRICK_TIERS;
      origin.x += BRICK_WIDTH;
    }
    origin.y += BRICK_HEIGHT;
  }
}

Rectangle *GetPaddleQuad() {
  int index = paddle.index;

  QuadNode *temp = paddleQuads[index];
  if (temp->skin == paddle.skin && temp->quad.width == paddle.width) {
    return &temp->quad;
  }

  return NULL;
}

Rectangle *GetBallQuad() {

  QuadNode *temp = ballQuads[ball.skin];
  if (temp->skin == ball.skin) {
    return &temp->quad;
  }
  return NULL;
}

Rectangle *GetBrickQuad(Brick *brick) {
  QuadNode *temp = brickQuads[brick->index];
  if (temp->skin == brick->skin) {
    return &temp->quad;
  }
  return NULL;
}

void TableAdd(AssetNode *array[], const char *key, void *value) {
  int index = Hash(key);

  AssetNode *temp = malloc(sizeof(AssetNode));
  temp->key = key;
  temp->value = value;
  temp->next = array[index] ? array[index] : NULL;

  array[index] = temp;
}

void *TableGet(AssetNode *table[], const char *key) {
  int index = Hash(key);

  AssetNode *cursor = table[index];
  while (cursor) {
    if (strcmp(cursor->key, key) == 0) {
      return cursor->value;
    }
    cursor = cursor->next;
  }

  return NULL;
}

int Hash(const char *key) { return tolower(key[0]) % 26; }