#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window/Screen
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define VIRTUAL_WIDTH 432
#define VIRTUAL_HEIGHT 243

#define TARGET_FPS 60

// Fonts size
#define FONT_SMALL 8
#define FONT_MEDIUM 16
#define FONT_LARGE 32

// Text
#define GAME_TITLE "BREAKOUT"
#define OPTION_START "START"
#define OPTION_HIGH_SCORES "HIGH SCORES"
#define GAME_OVER_TEXT "GAME OVER"
#define FINAL_SCORE_TEXT "Final Score:"
#define CONTINUE_TEXT "Press Enter to continue!"

// Game
#define TIER_THRESHOLD 4

// Paddles
#define PADDLE_SPEED 200
#define STARTING_Y 32

// Balls
#define BALL_SIZE 8
#define BALL_MAX_STARTING_SPEED_X 200
#define BALL_MIN_STARTING_SPEED_Y -50
#define BALL_MAX_STARTING_SPEED_Y -60

// Bricks
#define BRICKS_ROW_MIN 1
#define BRICKS_ROW_MAX 5
#define BRICKS_COL_MIN 7
#define BRICKS_COL_MAX 13

// Player
#define MAX_HEALTH 3
#define HEART_WIDTH 10
#define HEART_HEIGHT 9

#endif