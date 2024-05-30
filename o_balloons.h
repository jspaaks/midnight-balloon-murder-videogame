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

int o_balloons_compare (const void *, const void *);
void o_balloons_draw (ctx_t *);
void o_balloons_free (balloon_t *);
balloon_t * o_balloons_malloc (ctx_t *);
balloon_t * o_balloons_populate (ctx_t *);
balloon_t * o_balloons_randomize_t (ctx_t *);
balloon_t * o_balloons_randomize_x (ctx_t *);
balloon_t * o_balloons_sort (ctx_t *);
void o_balloons_update (ctx_t *);

#endif
