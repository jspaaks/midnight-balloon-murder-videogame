#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "SDL_render.h"
#include "types.h"

void spritesheet_deinit (SDL_Texture **);
SDL_Texture * spritesheet_init (SDL_Renderer *, char *);

#endif
