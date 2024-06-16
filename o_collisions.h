#ifndef O_COLLISIONS_H
#define O_COLLISIONS_H
#include "types.h"

void o_collisions_deinit (collision_t **);
void o_collisions_draw (SDL_Renderer *, SDL_Texture *, scene_t, collision_t *);
collision_t * o_collisions_init (void);
void o_collisions_update (timing_t, scene_t, ground_t, ctx_t *, counters_t *, balloon_t **, bullet_t **, collision_t **);

#endif
