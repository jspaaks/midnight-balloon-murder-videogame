#include <stdlib.h>
#include "o_balloons.h"
#include "context.h"
#include "constants.h"
#include "levels.h"
#include <SDL_timer.h>

static int o_balloons_compare (const void *, const void *);
static balloon_t * o_balloons_malloc (ctx_t *);
static balloon_t * o_balloons_populate (ctx_t *);
static balloon_t * o_balloons_randomize_t (ctx_t *);
static balloon_t * o_balloons_randomize_x (ctx_t *);
static balloon_t * o_balloons_sort (ctx_t *);
static bool o_balloons_is_outside(balloon_t *);

static const SDL_Rect src_yellow = {
    .x = 166,
    .y = 1,
    .w = 12,
    .h = 16,
};
static const SDL_Rect src_orange = {
    .x = 184,
    .y = 1,
    .w = 9,
    .h = 12,
};
static const SDL_Rect src_red = {
    .x = 184,
    .y = 20,
    .w = 6,
    .h = 7,
};
static balloon_t balloon_red = {
    .x = 0,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = src_red.w,
    .h = src_red.h,
    .u = 0.0,
    .v = -30.0,
    .value = 5,
    .state = PRESPAWN,
    .src = &src_red,
    .tgt = {
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
        .w = src_red.w,
        .h = src_red.h,
    },
    .trelease = 0,
};
static balloon_t balloon_orange = {
    .x = 0,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = src_orange.w,
    .h = src_orange.h,
    .u = 0.0,
    .v = -30.0,
    .value = 4,
    .state = PRESPAWN,
    .src = &src_orange,
    .tgt = {
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
        .w = src_orange.w,
        .h = src_orange.h,
    },
    .trelease = 0,
};
static balloon_t balloon_yellow = {
    .x = 0,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = src_yellow.w,
    .h = src_yellow.h,
    .u = 0.0,
    .v = -30.0,
    .value = 3,
    .state = PRESPAWN,
    .src = &src_yellow,
    .tgt = {
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
        .w = src_yellow.w,
        .h = src_yellow.h,
    },
    .trelease = 0,
};

static int o_balloons_compare (const void * a, const void * b) {
    const balloon_t * aa = a;
    const balloon_t * bb = b;
    if (aa->value < bb->value) {
        return -1;
    } else if (aa->value == bb->value) {
        return 0;
    } else {
        return 1;
    }
}

void o_balloons_draw (ctx_t * ctx) {
    for (int i = 0; i < ctx->level->nballoons; i++) {
        if (ctx->balloons[i].state == AIRBORNE) {
            SDL_RenderCopy(ctx->renderer, ctx->spritesheet, ctx->balloons[i].src, &ctx->balloons[i].tgt);
        }
    }
}

void o_balloons_free (balloon_t * balloons) {
    free(balloons);
}

ctx_t * o_balloons_init (ctx_t * ctx) {
    ctx->balloons = o_balloons_malloc(ctx);
    if (ctx->balloons == NULL) {
        fprintf(stderr, "Something went wrong allocating memory for the balloons.\n");
        exit(EXIT_FAILURE);
    }
    ctx->balloons = o_balloons_populate(ctx);
    ctx->balloons = o_balloons_randomize_x(ctx);
    ctx->balloons = o_balloons_randomize_t(ctx);
    ctx->balloons = o_balloons_sort(ctx);
    ctx->nprespawn = ctx->level->nballoons;
    ctx->nairborne = 0;
    ctx->nhit = 0;
    ctx->nmiss = 0;
    return ctx;
}

static balloon_t * o_balloons_malloc (ctx_t * ctx) {
    balloon_t * balloons = malloc(ctx->level->nballoons * sizeof(balloon_t));
    return balloons;
}

static balloon_t * o_balloons_populate (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    for (int i = 0; i < ctx->level->nred; i++, b++) {
        *b = balloon_red;
    }
    for (int i = 0; i < ctx->level->norange; i++, b++) {
        *b = balloon_orange;
    }
    for (int i = 0; i < ctx->level->nyellow; i++, b++) {
        *b = balloon_yellow;
    }
    return ctx->balloons;
}

static balloon_t * o_balloons_randomize_t (ctx_t * ctx) {
    static const float spawn_rate = 0.35; // balloons per second
    balloon_t * b = ctx->balloons;
    const int t_ampl = (int) 1000 * ctx->level->nballoons / spawn_rate;
    Uint64 tnow = SDL_GetTicks64();
    for (int i = 0; i < ctx->level->nballoons; i++, b++) {
        b->trelease = tnow + rand() % t_ampl;
    }
    return ctx->balloons;
}

static balloon_t * o_balloons_randomize_x (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    const int x_ampl = (int) (0.5 * SCREEN_WIDTH);
    int r;
    for (int i = 0; i < ctx->level->nballoons; i++, b++) {
        r = rand() % x_ampl;
        int x = (0.4 * SCREEN_WIDTH) + r;
        b->x = x;
        b->tgt.x = x;
    }
    return ctx->balloons;
}

static balloon_t * o_balloons_sort (ctx_t * ctx) {
    // TODO sort by balloon type
    size_t nitems = ctx->level->nballoons;
    size_t size = sizeof(balloon_t);
    void * base = (void *) ctx->balloons;
    qsort(base, nitems, size, o_balloons_compare);
    return ctx->balloons;
}

ctx_t * o_balloons_update (ctx_t * ctx) {
    for (int i = 0; i < ctx->level->nballoons; i++) {
        switch (ctx->balloons[i].state) {
            case PRESPAWN: {
                if (SDL_GetTicks64() > ctx->balloons[i].trelease) {
                    ctx->balloons[i].state = AIRBORNE;
                }
                break;
            }
            case AIRBORNE: {
                ctx->balloons[i].x += ctx->balloons[i].u * ctx->dt;
                ctx->balloons[i].y += ctx->balloons[i].v * ctx->dt;
                ctx->balloons[i].tgt.x = (int) ctx->balloons[i].x;
                ctx->balloons[i].tgt.y = (int) ctx->balloons[i].y;
                if (o_balloons_is_outside(&ctx->balloons[i])) {
                    ctx->balloons[i].state = MISS;
                }
                break;
            }
            case HIT: {
                // do nothing
                break;
            }
            case MISS: {
                // do nothing
                break;
            }
            default: {
                fprintf(stderr, "Something is wrong with the balloon states.\n");
                break;
            }
        }
    }
    return ctx;
}

static bool o_balloons_is_outside(balloon_t * balloon) {
    return balloon->tgt.y + balloon->h < 0 ||
           balloon->tgt.y > SCREEN_HEIGHT  ||
           balloon->tgt.x + balloon->w < 0 ||
           balloon->tgt.x > SCREEN_WIDTH;
}
