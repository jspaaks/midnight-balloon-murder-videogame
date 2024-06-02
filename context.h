#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_rect.h>
#include <stdbool.h>

typedef struct ctx_t ctx_t;
typedef struct turret_t turret_t;
typedef struct barrel_t barrel_t;
typedef struct flash_t flash_t;

struct turret_t {
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct barrel_t {
    float angle;
    float length;
    float speed;
    SDL_FPoint pivot;
    SDL_FRect sim;
    SDL_Point pivot_offset;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct flash_t {
    SDL_Point pivot_offset;
    bool show;
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct balloon_t; // incomplete type instead of #include "o_balloons.h"
struct bullet_t;  // incomplete type instead of #include "o_bullets.h"
struct level_t;   // incomplete type instead of #include "levels.h"

struct ctx_t {
    const Uint8 * keys;
    float dt;
    int nairborne;
    int nbullets;
    int nhit;
    int nlevels;
    int nmiss;
    int nprespawn;
    SDL_Renderer * renderer;
    SDL_Texture * spritesheet;
    SDL_Window * window;
    struct balloon_t * balloons;
    struct barrel_t barrel;
    struct bullet_t * bullets;
    struct flash_t flash;
    struct level_t * level;
    struct level_t * levels;
    struct turret_t turret;
};

#endif
