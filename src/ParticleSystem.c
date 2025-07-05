// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "ParticleSystem.h"
#include <stdlib.h>

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

// --------------------------------------------------
// Functions
// --------------------------------------------------
ParticleSystem *newParticleSystem(Texture2D texture, int particles) {
  ParticleSystem *ps = malloc(sizeof(ParticleSystem));
  ps->texture = texture;
  ps->particles = particles;
  ps->particleArray = malloc(sizeof(Particle));
  return ps;
}

void PS_SetParticleLifetime(ParticleSystem *ps, float min, float max) {
  ps->minLifetime = min;
  ps->maxLifetime = max;
}

void PS_SetLinearAcceleration(ParticleSystem *ps, float xMin, float yMin,
                              float xMax, float yMax) {
  ps->minLinearAccelerationX = xMin;
  ps->minLinearAccelerationY = yMin;
  ps->maxLinearAccelerationX = xMax;
  ps->maxLinearAccelerationY = yMax;
}

void PS_SetEmissionArea(ParticleSystem *ps, Distribution dist, unsigned int dx,
                        unsigned int dy) {
  ps->distribution = dist;
  ps->maxSpawnDistanceX = dx;
  ps->maxSpawnDistanceY = dy;
}

void PS_SetColors(ParticleSystem *ps, int r1, int g1, int b1, int a1, int r2,
                  int g2, int b2, int a2) {}

void PS_Emit(ParticleSystem *ps) {}

void PS_Update(ParticleSystem *ps, float dt) {
  for (int i = 0; i < ps->particles; i++) {
    ParticleUpdate(ps->particleArray[i]);
  }
}

void ParticleUpdate(Particle *p) {}