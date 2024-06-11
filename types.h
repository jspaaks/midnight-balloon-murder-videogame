#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_rect.h"
#include "SDL_ttf.h"

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
typedef struct ground_t ground_t;
typedef struct legend_t legend_t;
typedef struct level_t level_t;
typedef struct moon_t moon_t;
typedef struct scene_t scene_t;
typedef struct state_t state_t;
typedef struct turret_t turret_t;

struct balloon_t {
    bool delete;
    struct balloon_t * next;
    SDL_FRect sim;
    struct {
        float u;
        float v;
    } sim2;
    SDL_Rect src;
    unsigned int value;
};

struct barrel_t {
    SDL_FRect sim;
    struct {
        float angle;
        SDL_FPoint pivot;
        SDL_FPoint pivot_offset;
        float length;
        float speed;
    } sim2;
    SDL_Rect src;
};

struct bullet_t {
    bool delete;
    const SDL_Rect * src;
    SDL_FRect sim;
    struct {
        float u;
        float v;
    } sim2;
    struct bullet_t * next;
};

struct collision_t {
    SDL_FPoint sim;
    struct {
        float u;
        float v;
    } sim2;
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

    bool show;
    SDL_FRect sim;
    struct {
        SDL_FPoint pivot_offset;
    } sim2;
    SDL_Rect src;
};

struct ground_t {
    SDL_FRect sim;
};

struct legend_t {
    unsigned int nbars;
    struct {
        SDL_FRect sim;
    } bars[10];
    struct {
        SDL_FRect sim;
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

struct moon_t {
    SDL_FRect sim;
    SDL_Rect src;
};

struct scene_t {
    bool resized;
    float scale;
    float ratio;
    SDL_FRect sim;
    SDL_Rect tgt;
};

struct state_t {
    void (*draw)(ctx_t *);
    ctx_t * (*update)(ctx_t *, struct state_t **);
    state_name_t label;
};

struct turret_t {
    SDL_FRect sim;
    SDL_Rect src;
};

struct ctx_t {
    bool resized;
    bool isfullscreen;
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
    ground_t ground;
    moon_t moon;
    legend_t legend;
    level_t * level;
    level_t * levels;
    scene_t scene;
    turret_t turret;
    Uint64 tspawn_latestbullet;
};

#endif
