#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_rect.h"
#include "SDL_ttf.h"

typedef enum {BA_PRESPAWN, BA_AIRBORNE, BA_HIT, BA_MISS} balloon_state_t;
typedef enum {BU_AIRBORNE, BU_HIT} bullet_state_t;

typedef struct balloon_t balloon_t;
typedef struct barrel_t barrel_t;
typedef struct bullet_t bullet_t;
typedef struct collision_t collision_t;
typedef struct colors_t colors_t;
typedef struct ctx_t ctx_t;
typedef struct flash_t flash_t;
typedef struct legend_t legend_t;
typedef struct level_t level_t;
typedef struct turret_t turret_t;

struct balloon_t {
    float u;
    float v;
    unsigned int value;
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
    bullet_state_t state;
    const SDL_Rect * src;
    SDL_Rect tgt;
    SDL_FRect sim;
    struct bullet_t * next;
};

struct collision_t {
    Uint64 tspawn;
    SDL_FPoint sim;
    struct collision_t * next;
};

struct colors_t {
    SDL_Color bg;
    SDL_Color green;
    SDL_Color hit;
    SDL_Color lightgray;
    SDL_Color magenta;
    SDL_Color middlegray;
    SDL_Color miss;
    SDL_Color none;
    SDL_Color orange;
    SDL_Color red;
    SDL_Color white;
};

struct flash_t {
    SDL_Point pivot_offset;
    bool show;
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct legend_t {
    unsigned int nbars;
    struct {
        SDL_Rect tgt;
    } bars[10];
    struct {
        SDL_Rect tgt;
        SDL_Color * bg;
    } highlight;
};

struct level_t {
    unsigned int nballoons;
    unsigned int nbullets;
    unsigned int norange;
    unsigned int nred;
    unsigned int nyellow;
    char name[20];
};

struct turret_t {
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct ctx_t {
    const Uint8 * keys;
    struct {
        float frame;    // s
    } dt;
    unsigned int nairborne;
    unsigned int nbullets;
    unsigned int nhit;
    unsigned int nlevels;
    unsigned int nmiss;
    unsigned int nprespawn;
    SDL_Renderer * renderer;
    SDL_Texture * spritesheet;
    SDL_Window * window;
    TTF_Font * font;
    struct balloon_t * balloons;
    struct barrel_t barrel;
    struct bullet_t * bullets;
    struct collision_t * collisions;
    struct colors_t colors;
    struct flash_t flash;
    struct legend_t legend;
    struct level_t * level;
    struct level_t * levels;
    struct turret_t turret;
    Uint64 tspawn_latestbullet;
};

#endif
