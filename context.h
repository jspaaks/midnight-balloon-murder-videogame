#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL_video.h>
#include <SDL_render.h>

typedef struct {
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * spritesheet;
    const Uint8 * keys;
} ctx_t;

#endif
