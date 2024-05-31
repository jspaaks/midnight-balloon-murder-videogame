#ifndef O_BULLETS_H
#define O_BULLETS_H
#include "context.h"

typedef struct bullet_t bullet_t;

struct bullet_t {
    double x;
    double y;
    double u;
    double v;
    int w;
    int h;
    Uint64 spawned;
    const SDL_Rect * src;
    SDL_Rect tgt;
    struct bullet_t * next;
};

void o_bullets_draw (ctx_t *);
ctx_t * o_bullets_init (ctx_t *);
void o_bullets_update (ctx_t *);

#endif
