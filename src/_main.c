// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "_Dependencies.h"

// --------------------------------------------------
// Defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
void Init(void);
void LoadFonts(void);
void LoadTextures(void);
void LoadSounds(void);
void LoadMusic(void);

void UpdateAll(float dt);
void DrawAll(void);
void DrawToVirtualScreen(void);
void DrawToWindow(void);

// --------------------------------------------------
// Variables
// --------------------------------------------------
extern State stateStart;

RenderTexture2D vScreen;

Font gFont;
Texture2D gBackground, gMain, gArrows, gHearts, gParticle;
Sound gPaddleHit, gScore, gWallHit, gConfirm, gSelect, gNoSelect, gBrickHit1,
    gBrickHit2, gHurt, gVictory, gRecover, gHighScore, gPause;
Music gMusic;

float dt;

// --------------------------------------------------
// Program main entry point
// --------------------------------------------------
int main(void) {
  Init();

  sm_change_state(&stateStart, NULL);
  while (!WindowShouldClose()) {
    dt = GetFrameTime();
    UpdateAll(dt);
    DrawAll();
  }

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

  SetTargetFPS(TARGET_FPS);

  LoadFonts();
  LoadTextures();
  LoadSounds();
}

void LoadFonts(void) { gFont = LoadFont("./assets/fonts/font.ttf"); }

void LoadTextures(void) {
  gBackground = LoadTexture("./assets/graphics/background.png");
  gMain = LoadTexture("./assets/graphics/breakout.png");
  gArrows = LoadTexture("./assets/graphics/arrows.png");
  gHearts = LoadTexture("./assets/graphics/hearts.png");
  gParticle = LoadTexture("./assets/graphics/particle.png");
}

void LoadSounds(void) {
  gPaddleHit = LoadSound("./assets/sounds/paddle_hit.wav");
  gScore = LoadSound("./assets/sounds/score.wav");
  gWallHit = LoadSound("./assets/sounds/wall_hit.wav");
  gConfirm = LoadSound("./assets/sounds/confirm.wav");
  gSelect = LoadSound("./assets/sounds/select.wav");
  gNoSelect = LoadSound("./assets/sounds/no_select.wav");
  gBrickHit1 = LoadSound("./assets/sounds/brick-hit-1.wav");
  gBrickHit2 = LoadSound("./assets/sounds/brick-hit-2.wav");
  gHurt = LoadSound("./assets/sounds/hurt.wav");
  gVictory = LoadSound("./assets/sounds/victory.wav");
  gRecover = LoadSound("./assets/sounds/recover.wav");
  gHighScore = LoadSound("./assets/sounds/high_score.wav");
  gPause = LoadSound("./assets/sounds/pause.wav");
}

void LoadMusic(void) { gMusic = LoadMusicStream("./assets/musics/music.wav"); }

void UpdateAll(float dt) { sm_update(dt); }

void DrawAll(void) {
  DrawToVirtualScreen();
  DrawToWindow();
}

void DrawToVirtualScreen(void) {
  BeginTextureMode(vScreen);
  ClearBackground(BLACK);
  Rectangle source = {0, 0, gBackground.width, gBackground.height};
  Rectangle dest = {0, 0, VIRTUAL_WIDTH + 2, VIRTUAL_HEIGHT + 2};
  DrawTexturePro(gBackground, source, dest, (Vector2){0, 0}, 0, WHITE);
  sm_draw();
  DrawFPS(5, 5);
  EndTextureMode();
}

void DrawToWindow(void) {
  BeginDrawing();
  Rectangle source = {0, 0, vScreen.texture.width, -vScreen.texture.height};

  Rectangle dest = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  DrawTexturePro(vScreen.texture, source, dest, (Vector2){0, 0}, 0, WHITE);
  EndDrawing();
}