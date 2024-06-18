#ifndef DRAWABLE_MOON_H
#define DRAWABLE_MOON_H
#include "types.h"

void drawable_moon_draw (SDL_Renderer *, SDL_Texture *, scene_t, moon_t);
moon_t drawable_moon_init(scene_t);

#endif
