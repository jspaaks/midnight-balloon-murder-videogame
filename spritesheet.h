#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "SDL_render.h"
#include "types.h"

void spritesheet_deinit (ctx_t *);
void spritesheet_init (ctx_t *, SDL_Renderer *);

#endif
