#ifndef TYPES_H
#define TYPES_H

#include <SDL_video.h>
#include <SDL_render.h>

typedef struct {
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * sprites;
} ctx_t;

#endif
