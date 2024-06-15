#ifndef O_COLLISIONS_H
#define O_COLLISIONS_H
#include "types.h"

void o_collisions_deinit (collision_t **);
void o_collisions_draw (SDL_Renderer *, scene_t, SDL_Texture *, collision_t *);
void o_collisions_init (collision_t **);
void o_collisions_update (scene_t, ground_t, ctx_t *, balloon_t **, bullet_t **, collision_t **);

#endif
