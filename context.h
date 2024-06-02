#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_rect.h>
#include <stdbool.h>

typedef enum {PRESPAWN, AIRBORNE, HIT, MISS} balloon_state_t;

typedef struct balloon_t balloon_t;
typedef struct barrel_t barrel_t;
typedef struct bullet_t bullet_t;
typedef struct ctx_t ctx_t;
typedef struct flash_t flash_t;
typedef struct level_t level_t;
typedef struct turret_t turret_t;

struct balloon_t {
    float u;
    float v;
    int value;
    balloon_state_t state;
    SDL_FRect sim;
    const SDL_Rect * src;
    SDL_Rect tgt;
    Uint64 trelease;
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

struct bullet_t {
    float u;
    float v;
    Uint64 spawned;
    const SDL_Rect * src;
    SDL_Rect tgt;
    SDL_FRect sim;
    struct bullet_t * next;
};

struct flash_t {
    SDL_Point pivot_offset;
    bool show;
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct level_t {
    int nballoons;
    int nbullets;
    int norange;
    int nred;
    int nyellow;
    char name[20];
};

struct turret_t {
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

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
