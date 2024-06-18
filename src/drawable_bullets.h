#ifndef O_BULLETS_H
#define O_BULLETS_H
#include "types.h"

void drawable_bullets_deinit (bullet_t **);
void drawable_bullets_draw (SDL_Renderer *, SDL_Texture *, scene_t, bullet_t *);
bullet_t * drawable_bullets_init (void);
void drawable_bullets_update (timing_t, scene_t, ground_t, chunks_t, counters_t *,
                              barrel_t *, flash_t *, bullet_t **);

#endif
