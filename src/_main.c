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
void LoadAndStoreTextures(char *key, const char *path);
void LoadSounds(void);
void LoadAndStoreSounds(char *key, const char *path);
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
Music gMusic;

float dt;

// QuadNode **gFrames[32];

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

  SetRandomSeed(time(NULL));

  LoadFonts();
  LoadTextures();
  LoadSounds();

  GenerateAllQuads(*(Texture2D *)(TableGet(gTextures, "main")));
}

void LoadFonts(void) { gFont = LoadFont("./assets/fonts/font.ttf"); }

void LoadTextures(void) {
  LoadAndStoreTextures("background", "./assets/graphics/background.png");
  LoadAndStoreTextures("main", "./assets/graphics/breakout.png");
  LoadAndStoreTextures("arrows", "./assets/graphics/arrows.png");
  LoadAndStoreTextures("hearts", "./assets/graphics/hearts.png");
  LoadAndStoreTextures("particle", "./assets/graphics/particle.png");
}

void LoadAndStoreTextures(char *key, const char *path) {
  Texture2D *temp = malloc(sizeof(Texture2D));
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

void LoadAndStoreSounds(char *key, const char *path) {
  Sound *temp = malloc(sizeof(Sound));
  *temp = LoadSound(path);
  TableAdd(gSounds, key, (void *)temp);
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

  Texture2D *bg = TableGet(gTextures, "background");
  Rectangle source = {0, 0, bg->width, bg->height};
  Rectangle dest = {0, 0, VIRTUAL_WIDTH + 2, VIRTUAL_HEIGHT + 2};
  DrawTexturePro(*bg, source, dest, (Vector2){0, 0}, 0, WHITE);

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