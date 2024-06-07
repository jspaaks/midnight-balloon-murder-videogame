#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_rect.h"
#include "SDL_ttf.h"

typedef enum {
    BA_PRESPAWN,
    BA_AIRBORNE,
    BA_HIT,
    BA_MISS
} balloon_state_t;

typedef enum {
    BU_AIRBORNE,
    BU_HIT
} bullet_state_t;

typedef enum {
    START = 0,
    PLAYING,
    PAUSED,
    LEVEL_FINISHED,
} state_name_t;

typedef struct balloon_t balloon_t;
typedef struct barrel_t barrel_t;
typedef struct bullet_t bullet_t;
typedef struct collision_t collision_t;
typedef struct colors_t colors_t;
typedef struct ctx_t ctx_t;
typedef struct flash_t flash_t;
typedef struct legend_t legend_t;
typedef struct level_t level_t;
typedef struct state_t state_t;
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
    SDL_Color ground;
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
    unsigned int norange;
    unsigned int nproceed;
    unsigned int nred;
    unsigned int nyellow;
    char name[20];
    struct {
        unsigned int ba;
        unsigned int bu;
    } nprespawn;
};

struct state_t {
    void (*draw)(ctx_t *);
    ctx_t * (*update)(ctx_t *, struct state_t **);
    state_name_t label;
};

struct turret_t {
    SDL_FRect sim;
    SDL_Rect src;
    SDL_Rect tgt;
};

struct ctx_t {
    unsigned int ilevel;
    unsigned int ilevel_unlocked;
    unsigned int nhit;
    unsigned int nlevels;
    unsigned int nmiss;
    const Uint8 * keys;
    struct {
        float frame;    // s
    } dt;
    struct {
        unsigned int ba;
        unsigned int bu;
    } nairborne;
    struct {
        unsigned int ba;
        unsigned int bu;
    } nprespawn;
    SDL_Renderer * renderer;
    SDL_Texture * spritesheet;
    SDL_Window * window;
    struct {
        TTF_Font * regular;
        TTF_Font * large;
        TTF_Font * xlarge;
        TTF_Font * xxlarge;
        TTF_Font * xxxlarge;
    } fonts;
    balloon_t * balloons;
    barrel_t barrel;
    bullet_t * bullets;
    collision_t * collisions;
    colors_t colors;
    flash_t flash;
    legend_t legend;
    level_t * level;
    level_t * levels;
    turret_t turret;
    Uint64 tspawn_latestbullet;
};

#endif
