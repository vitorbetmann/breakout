#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H
// --------------------------------------------------
// Includes
// --------------------------------------------------
#include <raylib.h>

// --------------------------------------------------
// Other defines
// --------------------------------------------------

// --------------------------------------------------
// Data types
// --------------------------------------------------
typedef enum { NORMAL, UNIFORM } Distribution;

typedef struct {
  Vector2 pos;
  float dx, dy;
  float lifeTime, initialLifeTime;
  float linearAccelerationX, linearAccelerationY;
  float spawnDistanceX, spawnDistanceY;
  Texture2D *texture;
  Color initialColor, currColor, finalColor;
  Color colorDelta;
} Particle;

typedef struct {
  Vector2 pos;
  Texture2D *texture;
  int particles;
  Particle **particleArray;
  float minLifetime, maxLifetime;
  int minLinearAccelerationX, maxLinearAccelerationX;
  int minLinearAccelerationY, maxLinearAccelerationY;
  int standardDeviationX, standardDeviationY;
  unsigned int maxSpawnDistanceX, maxSpawnDistanceY;
  Distribution distribution;
  bool canEmit;
  Color initialColor, finalColor;
} ParticleSystem;

typedef struct PS_NODE {
  ParticleSystem ps;
  struct PS_NODE *next;
} ParticleSystemNode;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
ParticleSystem *newParticleSystem(Texture2D *texture, int particles,
                                  Vector2 pos, float lifeMin, float lifeMax,
                                  float ddxMin, float ddyMin, float ddxMax,
                                  float ddyMax, Distribution dist,
                                  unsigned int dx, unsigned int dy);

void PS_SetColors(ParticleSystem *ps, Color color1, Color color2);
void PS_Emit(ParticleSystem *ps);
void PS_Update(ParticleSystem *ps, float dt);
void ParticleUpdate(Particle *p, float dt);
void PS_Draw(ParticleSystem *ps);
void ParticleDraw(Particle *p);

void UnloadParticleSystem(ParticleSystem *ps);

#endif