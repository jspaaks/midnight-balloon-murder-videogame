#ifndef RENDERER_H
#define RENDERER_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void renderer_deinit (SDL_Renderer **);
void renderer_init (SDL_Window *, SDL_Renderer **);

#endif
