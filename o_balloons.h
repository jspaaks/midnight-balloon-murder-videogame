#ifndef BALLOONS_H
#define BALLOONS_H
#include <stdbool.h>
#include "context.h"
#include <SDL_rect.h>

typedef enum {PRESPAWN, AIRBORNE, HIT, MISS} balloon_state_t;

typedef struct  balloon_t balloon_t;

struct balloon_t {
    double x;
    double y;
    int w;
    int h;
    double u;
    double v;
    int value;
    balloon_state_t state;
    const SDL_Rect * src;
    SDL_Rect tgt;
    Uint64 trelease;
};

void o_balloons_draw (ctx_t *);
void o_balloons_free (balloon_t *);
ctx_t * o_balloons_init (ctx_t *);
ctx_t * o_balloons_update (ctx_t *);

#endif
