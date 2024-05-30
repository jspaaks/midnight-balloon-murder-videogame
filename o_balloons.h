#ifndef BALLOONS_H
#define BALLOONS_H
#include <stdbool.h>
#include "context.h"
#include <SDL_rect.h>

typedef enum {PRESPAWN, AIRBORNE, HIT, MISS} balloon_state_t;

typedef struct {
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
} balloon_t;

void balloons_draw (ctx_t *);
void balloons_update (void);

#endif
