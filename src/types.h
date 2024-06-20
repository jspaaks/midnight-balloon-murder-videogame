#ifndef TYPES_H
#define TYPES_H

#include "SDL_mixer.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include <stdbool.h>

typedef enum {
    ALIVE = 0,
    EXITED,
    HIT,
    TIMEOUT_ENDED,
} delete_reason_t;

typedef enum {
    GAMESTATE_STARTING = 0,
    GAMESTATE_PLAYING,
    GAMESTATE_PAUSING,
    GAMESTATE_FINISHING_LEVEL,
} gamestate_enum_t;

typedef enum {
    LEVEL_NOVICE = 0,
    LEVEL_PRIVATE,
    LEVEL_GUNNY,
    LEVEL_SHARPSHOOTER,
    LEVEL_ASSASSIN,
    LEVEL_BERSERKER,
} level_enum_t;

typedef struct balloon_t balloon_t;
typedef struct barrel_t barrel_t;
typedef struct bullet_t bullet_t;
typedef struct chunks_t chunks_t;
typedef struct collision_t collision_t;
typedef struct colors_t colors_t;
typedef struct counters_t counters_t;
typedef struct drawables_t drawables_t;
typedef struct drawing_t drawing_t;
typedef struct flash_t flash_t;
typedef struct fonts_t fonts_t;
typedef struct gamestate_t gamestate_t;
typedef struct ground_t ground_t;
typedef struct legend_t legend_t;
typedef struct level_t level_t;
typedef struct moon_t moon_t;
typedef struct scene_t scene_t;
typedef struct timing_t timing_t;
typedef struct turret_t turret_t;

struct balloon_t {
    struct balloon_t * next;
    SDL_FRect sim;
    struct {
        float u;
        float v;
    } sim2;
    SDL_Rect src;
    delete_reason_t state;
    unsigned int value;
};

struct barrel_t {
    float countdown_duration;  // seconds
    float countdown_remaining; // seconds
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
    struct bullet_t * next;
    const SDL_Rect * src;
    SDL_FRect sim;
    struct {
        float u;
        float v;
    } sim2;
    delete_reason_t state;
};

struct chunks_t {
    Mix_Chunk * empty;
    struct {
        Mix_Chunk * orange;
        Mix_Chunk * red;
        Mix_Chunk * yellow;
    } hit;
    Mix_Chunk * pop;
    Mix_Chunk * shoot;
};

struct counters_t {
    struct {
        unsigned int airborne;
        unsigned int hit;
        unsigned int miss;
        unsigned int orange;
        unsigned int prespawn;
        unsigned int red;
        unsigned int yellow;
    } nballoons;
    struct {
        unsigned int airborne;
        unsigned int prespawn;
    } nbullets;
};

struct collision_t {
    float age;     // seconds
    float age_max; // seconds
    bool iseffect;
    struct collision_t * next;
    SDL_FRect sim;
    struct {
        float u;
        float v;
    } sim2;
    SDL_Rect src;
    delete_reason_t state;
    unsigned int value;
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
    float age;     // seconds
    float age_max; // seconds
    bool had_bullets;
    SDL_FRect sim;
    struct {
        SDL_FPoint pivot_offset;
    } sim2;
    SDL_Rect src;
};

struct fonts_t {
    TTF_Font * regular;
    TTF_Font * large;
    TTF_Font * xlarge;
    TTF_Font * xxlarge;
    TTF_Font * xxxlarge;
};

struct gamestate_t {
    void (*draw)(level_t, drawing_t, drawables_t, counters_t);
    void (*update)(timing_t, chunks_t, counters_t *, drawing_t *, drawables_t *, gamestate_t **,
                   level_t *);
    gamestate_enum_t label;
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
        SDL_Color bg;
    } highlight;
};

struct level_t {
    level_enum_t label;
    level_enum_t label_next;
    char name[20];
    struct {
        unsigned int orange;
        unsigned int prespawn;
        unsigned int proceed;
        unsigned int red;
        unsigned int yellow;
    } nballoons;
    struct {
        unsigned int prespawn;
    } nbullets;

    bool next_unlocked;
};

struct moon_t {
    SDL_FRect sim;
    SDL_Rect src;
};

struct scene_t {
    bool isfullscreen;
    bool resized;
    float scale;
    float ratio;
    SDL_FRect sim;
    SDL_Rect tgt;
};

struct turret_t {
    SDL_FRect sim;
    SDL_Rect src;
};

struct drawing_t {
    colors_t colors;
    fonts_t fonts;
    SDL_Renderer * renderer;
    scene_t scene;
    SDL_Texture * spritesheet;
    SDL_Window * window;
};

struct drawables_t {
    balloon_t * balloons;
    barrel_t barrel;
    bullet_t * bullets;
    collision_t * collisions;
    flash_t flash;
    ground_t ground;
    legend_t legend;
    moon_t moon;
    turret_t turret;
};

struct timing_t {
    struct {
        float frame; // seconds
    } dt;
};

#endif
