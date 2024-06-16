#ifndef O_BARREL_H
#define O_BARREL_H
#include "SDL_render.h"
#include "types.h"

void o_barrel_draw (SDL_Renderer *, SDL_Texture *, scene_t, barrel_t);
barrel_t o_barrel_init (turret_t);
void o_barrel_update (timing_t, barrel_t *);

#endif
