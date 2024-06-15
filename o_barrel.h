#ifndef O_BARREL_H
#define O_BARREL_H
#include "SDL_render.h"
#include "types.h"

void o_barrel_draw (SDL_Renderer *, scene_t, SDL_Texture *, barrel_t);
void o_barrel_init (turret_t, barrel_t *);
void o_barrel_update (ctx_t *, barrel_t *);

#endif
