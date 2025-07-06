// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "ParticleSystem.h"
#include "raylib.h"
#include "stdio.h"
#include <stddef.h>
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
ParticleSystem *newParticleSystem(Texture2D *texture, int particles,
                                  Vector2 pos, float lifeMin, float lifeMax,
                                  float ddxMin, float ddyMin, float ddxMax,
                                  float ddyMax, Distribution dist,
                                  unsigned int dx, unsigned int dy) {
  ParticleSystem *ps = malloc(sizeof(ParticleSystem));
  ps->pos.x = pos.x;
  ps->pos.y = pos.y;
  ps->texture = texture;
  ps->particles = particles;
  ps->minLifetime = lifeMin;
  ps->maxLifetime = lifeMax;
  ps->minLinearAccelerationX = ddxMin;
  ps->minLinearAccelerationY = ddyMin;
  ps->maxLinearAccelerationX = ddxMax;
  ps->maxLinearAccelerationY = ddyMax;
  ps->distribution = dist;
  ps->maxSpawnDistanceX = dx;
  ps->maxSpawnDistanceY = dy;

  ps->particleArray = malloc(ps->particles * sizeof(size_t));

  for (int i = 0; i < ps->particles; i++) {
    ps->particleArray[i] = malloc(sizeof(Particle));
    Particle *temp = ps->particleArray[i];
    temp->texture = ps->texture;
    temp->dx = temp->dy = 0.0f;

    temp->lifeTime = GetRandomValue(lifeMin, lifeMax) / 1000.0f;
    temp->initialLifeTime = temp->lifeTime;

    temp->linearAccelerationX = GetRandomValue(ddxMin, ddxMax);
    temp->linearAccelerationY = GetRandomValue(ddyMin, ddyMax);

    temp->pos.x = GetRandomValue(0, dx);
    temp->pos.x *= GetRandomValue(0, 1) == 0 ? 1 : -1;
    temp->pos.x += ps->pos.x;

    temp->pos.y = GetRandomValue(0, dy);
    temp->pos.y *= GetRandomValue(0, 1) == 0 ? 1 : -1;
    temp->pos.y += ps->pos.y;
  }

  ps->canEmit = false;
  return ps;
}

void PS_SetColors(ParticleSystem *ps, Color colors1, Color colors2) {

  ps->initialColor = colors1;
  ps->finalColor = colors2;

  float dr, dg, db, da;
  dr = ps->finalColor.r - ps->initialColor.r;
  dg = ps->finalColor.g - ps->initialColor.g;
  db = ps->finalColor.b - ps->initialColor.b;
  da = ps->finalColor.a - ps->initialColor.a;
  Color colorDelta = {ps->finalColor.r - ps->initialColor.r,
                      ps->finalColor.g - ps->initialColor.g,
                      ps->finalColor.b - ps->initialColor.b,
                      ps->finalColor.a - ps->initialColor.a};

  for (int i = 0; i < ps->particles; i++) {
    ps->particleArray[i]->initialColor = colors1;
    ps->particleArray[i]->currColor = colors1;
    ps->particleArray[i]->finalColor = colors2;
    ps->particleArray[i]->colorDelta = colorDelta;
  }
}

void PS_Emit(ParticleSystem *ps) {
  ps->canEmit = true;
  //
}

void PS_Update(ParticleSystem *ps, float dt) {
  if (!ps->canEmit) {
    return;
  }

  ps->maxLifetime -= dt;
  if (ps->maxLifetime <= 0) {
    UnloadParticleSystem(ps);
  } else {
    for (int i = 0; i < ps->particles; i++) {
      ParticleUpdate(ps->particleArray[i], dt);
    }
  }
}

void ParticleUpdate(Particle *p, float dt) {
  // Update speed and pos
  p->dx = p->linearAccelerationX;
  p->dy = p->linearAccelerationY;
  p->pos.x += p->dx * dt;
  p->pos.y += p->dy * dt;

  // Update color
  p->lifeTime -= dt;
  if (p->lifeTime < 0) {
    p->lifeTime = 0;
  }

  float ratio = p->initialLifeTime > 0 ? p->lifeTime / p->initialLifeTime : 0;

  // Linearly interpolate each colour channel
  p->currColor.r =
      p->finalColor.r + (p->initialColor.r - p->finalColor.r) * ratio;
  p->currColor.g =
      p->finalColor.g + (p->initialColor.g - p->finalColor.g) * ratio;
  p->currColor.b =
      p->finalColor.b + (p->initialColor.b - p->finalColor.b) * ratio;
  p->currColor.a =
      p->finalColor.a + (p->initialColor.a - p->finalColor.a) * ratio;
}

void PS_Draw(ParticleSystem *ps) {
  if (!ps->canEmit) {
    return;
  }

  for (int i = 0; i < ps->particles; i++) {
    ParticleDraw(ps->particleArray[i]);
  }
}

void ParticleDraw(Particle *p) {
  DrawTexture(*p->texture, p->pos.x, p->pos.y, p->currColor);
}

void UnloadParticleSystem(ParticleSystem *ps) {
  for (int i = 0; i < ps->particles; i++) {
    free(ps->particleArray[i]);
  }
  free(ps);
  ps = NULL;
}