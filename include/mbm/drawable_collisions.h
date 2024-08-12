#ifndef DRAWABLE_COLLISIONS_H
#define DRAWABLE_COLLISIONS_H
#include "mbm/types.h"

void drawable_collisions_deinit (collision_t **);
void drawable_collisions_draw (SDL_Renderer *, SDL_Texture *, colors_t, fonts_t, scene_t,
                               collision_t *);
collision_t * drawable_collisions_init (void);
void drawable_collisions_update (timing_t, scene_t, ground_t, chunks_t, balloon_t *, bullet_t *,
                                 counters_t *, collision_t **);
#endif
