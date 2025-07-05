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
} Particle;

typedef struct {
  Texture2D texture;
  int particles;
  Particle **particleArray;

  float minLifetime, maxLifetime;
  int minLinearAccelerationX, maxLinearAccelerationX;
  int minLinearAccelerationY, maxLinearAccelerationY;
  int standardDeviationX, standardDeviationY;
  unsigned int maxSpawnDistanceX, maxSpawnDistanceY;
  Distribution distribution;
} ParticleSystem;

// --------------------------------------------------
// Prototypes
// --------------------------------------------------
ParticleSystem *newParticleSystem(Texture2D texture, int particles);
void PS_SetParticleLifetime(ParticleSystem *ps, float min, float max);
void PS_SetLinearAcceleration(ParticleSystem *ps, float xMin, float yMin,
                              float xMax, float yMax);
void PS_SetEmissionArea(ParticleSystem *ps, Distribution dist, unsigned int dx,
                        unsigned int dy);
void PS_SetColors(ParticleSystem *ps, int r1, int g1, int b1, int a1, int r2,
                  int g2, int b2, int a2);
void PS_Emit(ParticleSystem *ps);
void PS_Update(ParticleSystem *ps, float dt);
void ParticleUpdate(Particle *p);

#endif