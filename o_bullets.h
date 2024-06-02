#ifndef O_BULLETS_H
#define O_BULLETS_H
#include "context.h"

typedef struct bullet_t bullet_t;

struct bullet_t {
    float u;
    float v;
    Uint64 spawned;
    const SDL_Rect * src;
    SDL_Rect tgt;
    SDL_FRect sim;
    struct bullet_t * next;
};

void o_bullets_draw (ctx_t *);
ctx_t * o_bullets_init (ctx_t *);
ctx_t * o_bullets_update (ctx_t *);

#endif
