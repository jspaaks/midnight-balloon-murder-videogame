#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL_video.h>
#include <SDL_render.h>

typedef struct ctx_t ctx_t;

struct balloon_t; // incomplete type instead of #include "o_balloons.h"
struct level_t;   // incomplete type instead of #include "levels.h"

struct ctx_t {
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * spritesheet;
    const Uint8 * keys;
    double dt;
    int nlevels;
    struct level_t * level;
    struct balloon_t * balloons;
    struct level_t * levels;
};

#endif
