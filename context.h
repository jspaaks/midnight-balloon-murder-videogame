#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL_video.h>
#include <SDL_render.h>

typedef struct ctx_t ctx_t;

struct balloon_t; // incomplete type instead of #include "o_balloons.h"
struct bullet_t;  // incomplete type instead of #include "o_bullets.h"
struct level_t;   // incomplete type instead of #include "levels.h"

struct ctx_t {
    int nairborne;
    int nbullets;
    int nhit;
    int nlevels;
    int nmiss;
    int nprespawn;
    double dt;
    double barrel_angle;
    const Uint8 * keys;
    SDL_Renderer * renderer;
    SDL_Texture * spritesheet;
    SDL_Window * window;
    struct balloon_t * balloons;
    struct bullet_t * bullets;
    struct level_t * level;
    struct level_t * levels;
};

#endif
