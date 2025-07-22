// TODO: free everything I'm mallocking

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "StateMachine.h"
#include "_Dependencies.h"
#include "states/StateGameInit.h"
#include "states/StateGameOver.h"
#include "states/StateHighScore.h"
#include "states/StatePaddleSelect.h"
#include "states/StatePlay.h"
#include "states/StateServe.h"
#include "states/StateStart.h"
#include "states/StateVictory.h"

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum { FULL, EMPTY } HeartState;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void Init(void);
void InitStates(void);
void LoadFonts(void);
void LoadTextures(void);
void LoadAndStoreTextures(const char *key, const char *path);
void LoadSounds(void);
void LoadAndStoreSounds(const char *key, const char *path);
void LoadMusic(void);

void UpdateAll(float dt);
void DrawAll(void);
void DrawToVirtualScreen(void);
void DrawBackground(void);
void DrawHearts(void);
void DrawScore(void);

void DrawToWindow(void);

void UnloadAll(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern State stateStart;

RenderTexture2D vScreen;

Font gFont;
Music gMusic;

float dt;
int gHealth = MAX_HEALTH;
int gScore;

unsigned int currLevel = 1;

// --------------------------------------------------
// Program main entry point
// --------------------------------------------------
int main(void) {
  Init();

  SM_ChangeStateTo("start", NULL);
  while (!WindowShouldClose()) {
    dt = GetFrameTime();
    UpdateAll(dt);
    DrawAll();
  }
  UnloadAll();

  return 0;
}

// --------------------------------------------------
// Functions
// --------------------------------------------------
void Init(void) {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");
  InitAudioDevice();

  vScreen = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

  SetTargetFPS(30);

  SetRandomSeed(time(NULL));

  LoadFonts();
  LoadTextures();
  LoadSounds();

  GenerateAllQuads(*(Texture2D *)(TableGet(gTextures, "main")));

  SM_Init();

  InitStates();
}

void InitStates(void) {
  SM_RegisterState("start", NULL, StateStartUpdate, StateStartDraw, NULL);
  //  SM_RegisterState("paddle select", StatePaddleSelectEnter,
  //                StatePaddleSelectUpdate, StatePaddleSelectDraw,
  //             StatePaddleSelectExit);
  SM_RegisterState("init", StateInitEnter, NULL, NULL, NULL);
  SM_RegisterState("serve", StateServeEnter, StateServeUpdate, StateServeDraw,
                   NULL);
  SM_RegisterState("play", StatePlayEnter, StatePlayUpdate, StatePlayDraw,
                   NULL);
  // SM_RegisterState("victory", StateVictoryEnter, StateVictoryUpdate,
  //              StateVictoryDraw, NULL);
  // SM_RegisterState("enter high score", StateEnterHighScoreEnter,
  //                  StateEnterHighScoreUpdate, StateEnterHighScoreDraw,
  //                  StateEnterHighScoreExit);
  // SM_RegisterState("high score", StateHighScoreEnter, StateHighScoreUpdate,
  //              StateHighScoreDraw, StateHighScoreExit);
  SM_RegisterState("game over", NULL, StateGameOverUpdate, StateGameOverDraw,
                   NULL);
}

void LoadFonts(void) { gFont = LoadFont("./assets/fonts/font.ttf"); }

void LoadTextures(void) {
  LoadAndStoreTextures("background", "./assets/graphics/background.png");
  LoadAndStoreTextures("main", "./assets/graphics/breakout.png");
  LoadAndStoreTextures("arrows", "./assets/graphics/arrows.png");
  LoadAndStoreTextures("hearts", "./assets/graphics/hearts.png");
  LoadAndStoreTextures("particle", "./assets/graphics/particle.png");
}

void LoadAndStoreTextures(const char *key, const char *path) {
  Texture2D *temp = malloc(sizeof(Texture2D));
  if (!temp) {
    return;
  }
  *temp = LoadTexture(path);
  TableAdd(gTextures, key, (void *)temp);
}

void LoadSounds(void) {
  LoadAndStoreSounds("paddle hit", "./assets/sounds/paddle_hit.wav");
  LoadAndStoreSounds("score", "./assets/sounds/score.wav");
  LoadAndStoreSounds("wall hit", "./assets/sounds/wall_hit.wav");
  LoadAndStoreSounds("confirm", "./assets/sounds/confirm.wav");
  LoadAndStoreSounds("select", "./assets/sounds/select.wav");
  LoadAndStoreSounds("no select", "./assets/sounds/no_select.wav");
  LoadAndStoreSounds("brick hit 1", "./assets/sounds/brick-hit-1.wav");
  LoadAndStoreSounds("brick hit 2", "./assets/sounds/brick-hit-2.wav");
  LoadAndStoreSounds("hurt", "./assets/sounds/hurt.wav");
  LoadAndStoreSounds("victory", "./assets/sounds/victory.wav");
  LoadAndStoreSounds("recover", "./assets/sounds/recover.wav");
  LoadAndStoreSounds("high score", "./assets/sounds/high_score.wav");
  LoadAndStoreSounds("pause", "./assets/sounds/pause.wav");
}

void LoadAndStoreSounds(const char *key, const char *path) {
  Sound *temp = malloc(sizeof(Sound));
  if (!temp) {
    return;
  }
  *temp = LoadSound(path);
  TableAdd(gSounds, key, (void *)temp);
}

void LoadMusic(void) { gMusic = LoadMusicStream("./assets/musics/music.wav"); }

void UpdateAll(float dt) { SM_Update(dt); }

void DrawAll(void) {
  DrawToVirtualScreen();
  DrawToWindow();
}

void DrawToVirtualScreen(void) {
  BeginTextureMode(vScreen);
  ClearBackground(BLACK);

  DrawBackground();
  DrawHearts();
  DrawScore();

  SM_Draw();
  DrawFPS(5, 5);
  EndTextureMode();
}

void DrawBackground(void) {
  Texture2D *bg = TableGet(gTextures, "background");
  Rectangle source = {0, 0, bg->width, bg->height};
  Rectangle dest = {0, 0, VIRTUAL_WIDTH + 2, VIRTUAL_HEIGHT + 2};
  DrawTexturePro(*bg, source, dest, (Vector2){0, 0}, 0, WHITE);
}

void DrawHearts(void) {
  Rectangle dest = {VIRTUAL_WIDTH - 100, 4, HEART_WIDTH, HEART_HEIGHT};

  for (int i = 0; i < gHealth; i++) {
    DrawTexturePro(*((Texture2D *)TableGet(gTextures, "hearts")),
                   *GetHeartQuad(FULL), dest, (Vector2){0, 0}, 0, WHITE);
    dest.x += HEART_WIDTH + 2;
  }

  // Empty hearts
  for (int i = 0; i < MAX_HEALTH - gHealth; i++) {
    DrawTexturePro(*((Texture2D *)TableGet(gTextures, "hearts")),
                   *GetHeartQuad(EMPTY), dest, (Vector2){0, 0}, 0, WHITE);
    dest.x += HEART_WIDTH + 2;
  }
}

void DrawScore(void) {
  Vector2 origin = {VIRTUAL_WIDTH - 60, 5};
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Score: %04d", gScore);
  DrawTextEx(gFont, buffer, origin, FONT_SMALL, 0, WHITE);
}

void DrawToWindow(void) {
  BeginDrawing();
  Rectangle source = {0, 0, vScreen.texture.width, -vScreen.texture.height};
  Rectangle dest = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  DrawTexturePro(vScreen.texture, source, dest, (Vector2){0, 0}, 0, WHITE);
  EndDrawing();
}

void UnloadAll(void) { MapUnload(); }