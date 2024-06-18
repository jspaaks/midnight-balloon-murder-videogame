#ifndef O_BARREL_H
#define O_BARREL_H
#include "SDL_render.h"
#include "types.h"

void drawable_barrel_draw (SDL_Renderer *, SDL_Texture *, scene_t, barrel_t);
barrel_t drawable_barrel_init(turret_t);
void drawable_barrel_update (timing_t, barrel_t *);

#endif
