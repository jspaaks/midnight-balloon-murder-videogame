#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "SDL_render.h"
#include "types.h"

void spritesheet_deinit (SDL_Texture **);
void spritesheet_init (SDL_Renderer *, SDL_Texture **);

#endif
