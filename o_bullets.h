#ifndef O_BULLETS_H
#define O_BULLETS_H
#include "types.h"

void o_bullets_deinit (bullet_t **);
void o_bullets_draw (SDL_Renderer *, SDL_Texture *, scene_t, bullet_t *);
void o_bullets_init (level_t *, ground_t, bullet_t **, counters_t *);
void o_bullets_update (timing_t, scene_t, ground_t, ctx_t *, counters_t *, barrel_t, bullet_t **);

#endif
