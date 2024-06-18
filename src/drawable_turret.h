#ifndef DRAWABLE_TURRET_H
#define DRAWABLE_TURRET_H
#include "SDL_render.h"
#include "types.h"

void drawable_turret_draw (SDL_Renderer *, SDL_Texture *, scene_t, turret_t);
turret_t drawable_turret_init(scene_t, ground_t);

#endif
