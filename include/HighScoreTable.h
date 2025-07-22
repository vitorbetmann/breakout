#ifndef HIGH_SCORE_TABLE_H
#define HIGH_SCORE_TABLE_H
// --------------------------------------------------
// Includes
// --------------------------------------------------

// --------------------------------------------------
// Other defines
// --------------------------------------------------
#define NAME_LEN 8
#define MAX_SCORES 10
#define BLANK_NAME "---"

// --------------------------------------------------
// Data types
// --------------------------------------------------

typedef struct {
  char *name;
  int score;
} PlayerData;

typedef struct {
  PlayerData highScores[MAX_SCORES];
  int highScoresCount;
  bool isLoaded;
} HighScoreTable;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------

PlayerData GetPlayerData(int pos);
void InsertScore(PlayerData pd);

// --------------------------------------------------
// Variables
// --------------------------------------------------

#endif