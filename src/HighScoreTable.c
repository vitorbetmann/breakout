// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "HighScoreTable.h"
#include "SaveLoadSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------

void LoadHighScoreTable(void);
void SortHighScoreTable(void);
void ShiftScores(int pos);

// --------------------------------------------------
// Variables
// --------------------------------------------------

static HighScoreTable hst;

// --------------------------------------------------
// Functions
// --------------------------------------------------

PlayerData GetPlayerData(int pos) {
  if (!hst.isLoaded) {
    LoadHighScoreTable();
  }

  if (pos >= hst.highScoresCount) {
    return (PlayerData){BLANK_NAME, 0};
  }

  return hst.highScores[pos];
}

void InsertScore(PlayerData pd) {

  if (!hst.isLoaded) {
    LoadHighScoreTable();
  }

  bool isTableNotFull = hst.highScoresCount < MAX_SCORES;
  bool isTableEmpty = hst.highScoresCount == 0;
  bool isScoreLowest = pd.score < hst.highScores[hst.highScoresCount - 1].score;
  if (isTableNotFull && (isTableEmpty || isScoreLowest)) {
    hst.highScoresCount++;
    hst.highScores[hst.highScoresCount - 1] = pd;
    return;
  }

  for (int i = 0; i < hst.highScoresCount; i++) {
    if (pd.score > hst.highScores[i].score) {
      ShiftScores(i);
      hst.highScores[i] = pd;
      return;
    }
  }
}

void ShiftScores(int pos) {

  if (pos > hst.highScoresCount || pos == MAX_SCORES - 1) {
    return;
  }

  if (hst.highScoresCount < MAX_SCORES) {
    hst.highScoresCount++;
  }

  for (int i = hst.highScoresCount - 2; i >= pos; i--) {
    hst.highScores[i + 1] = hst.highScores[i];
  }
}

void LoadHighScoreTable(void) {

  SLS_BeginLoadSession(NULL);
  for (int i = 0; i < MAX_SCORES && SLS_HasNext(); i++) {
    // TODO remember to free all
    hst.highScores[i].name = SLS_LoadNext();
    // TODO truncate name to 3 chars
    hst.highScores[i].score = atoi(SLS_LoadNext());
    hst.highScoresCount++;
  }
  SLS_EndLoadSession();

  SortHighScoreTable();

  hst.isLoaded = true;
}

void SortHighScoreTable(void) {
  // Use binary sort
}
