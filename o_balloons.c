#include <assert.h>
#include <stdlib.h>
#include "SDL_timer.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_error.h"
#include "types.h"
#include "constants.h"
#include "levels.h"
#include "o_balloons.h"

static int o_balloons_compare (const void *, const void *);
static balloon_t * o_balloons_populate (ctx_t *);
static balloon_t * o_balloons_randomize_t (ctx_t *);
static balloon_t * o_balloons_randomize_x (ctx_t *);
static balloon_t * o_balloons_sort (ctx_t *);
static bool o_balloons_is_outside(balloon_t *);

static const SDL_Rect src_yellow = {
    .h = 16,
    .w = 12,
    .x = 166,
    .y = 1,
};
static const SDL_Rect src_orange = {
    .h = 12,
    .w = 9,
    .x = 184,
    .y = 1,
};
static const SDL_Rect src_red = {
    .h = 7,
    .w = 6,
    .x = 184,
    .y = 20,
};
static balloon_t balloon_red = {
    .sim = {
        .h = src_red.h,
        .w = src_red.w,
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    },
    .src = &src_red,
    .state = BA_PRESPAWN,
    .tgt = {
        .h = src_red.h,
        .w = src_red.w,
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    },
    .trelease = 0,
    .u = 0.0,
    .v = -30.0,
    .value = 5,
};
static balloon_t balloon_orange = {
    .sim = {
        .h = src_orange.h,
        .w = src_orange.w,
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    },
    .src = &src_orange,
    .state = BA_PRESPAWN,
    .tgt = {
        .h = src_orange.h,
        .w = src_orange.w,
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    },
    .trelease = 0,
    .u = 0.0,
    .v = -30.0,
    .value = 4,
};
static balloon_t balloon_yellow = {
    .sim = {
        .h = src_yellow.h,
        .w = src_yellow.w,
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    },
    .src = &src_yellow,
    .state = BA_PRESPAWN,
    .tgt = {
        .h = src_yellow.h,
        .w = src_yellow.w,
        .x = 0,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    },
    .trelease = 0,
    .u = 0.0,
    .v = -30.0,
    .value = 3,
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
    for (unsigned int i = 0; i < ctx->level->nballoons; i++) {
        if (ctx->balloons[i].state == BA_AIRBORNE) {
            SDL_RenderCopy(ctx->renderer, ctx->spritesheet, ctx->balloons[i].src, &ctx->balloons[i].tgt);
        }
    }
}

ctx_t * o_balloons_deinit (ctx_t * ctx) {
    free(ctx->balloons);
    ctx->balloons = NULL;
    return ctx;
}

ctx_t * o_balloons_init (ctx_t * ctx) {
    assert(ctx->level != NULL && "levels needs to be initialized before balloons");
    ctx->balloons = malloc(ctx->level->nballoons * sizeof(balloon_t));
    if (ctx->balloons == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong allocating memory for the balloons: %s\n", SDL_GetError());
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

static balloon_t * o_balloons_populate (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    for (unsigned int i = 0; i < ctx->level->nred; i++, b++) {
        *b = balloon_red;
    }
    for (unsigned int i = 0; i < ctx->level->norange; i++, b++) {
        *b = balloon_orange;
    }
    for (unsigned int i = 0; i < ctx->level->nyellow; i++, b++) {
        *b = balloon_yellow;
    }
    return ctx->balloons;
}

static balloon_t * o_balloons_randomize_t (ctx_t * ctx) {
    static const float spawn_rate = 0.35; // balloons per second
    balloon_t * b = ctx->balloons;
    const int t_ampl = (int) 1000 * ctx->level->nballoons / spawn_rate;
    Uint64 tnow = SDL_GetTicks64();
    for (unsigned int i = 0; i < ctx->level->nballoons; i++, b++) {
        b->trelease = tnow + rand() % t_ampl;
    }
    return ctx->balloons;
}

static balloon_t * o_balloons_randomize_x (ctx_t * ctx) {
    balloon_t * b = ctx->balloons;
    const int x_ampl = (int) (0.5 * SCREEN_WIDTH);
    int r;
    for (unsigned int i = 0; i < ctx->level->nballoons; i++, b++) {
        r = rand() % x_ampl;
        int x = (0.4 * SCREEN_WIDTH) + r;
        b->sim.x = x;
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
    for (unsigned int i = 0; i < ctx->level->nballoons; i++) {
        switch (ctx->balloons[i].state) {
            case BA_PRESPAWN: {
                if (SDL_GetTicks64() > ctx->balloons[i].trelease) {
                    ctx->balloons[i].state = BA_AIRBORNE;
                }
                break;
            }
            case BA_AIRBORNE: {
                ctx->balloons[i].sim.x += ctx->balloons[i].u * ctx->dt.frame;
                ctx->balloons[i].sim.y += ctx->balloons[i].v * ctx->dt.frame;
                ctx->balloons[i].tgt.x = (int) ctx->balloons[i].sim.x;
                ctx->balloons[i].tgt.y = (int) ctx->balloons[i].sim.y;
                if (o_balloons_is_outside(&ctx->balloons[i])) {
                    ctx->balloons[i].state = BA_MISS;
                }
                break;
            }
            case BA_HIT: {
                // do nothing
                break;
            }
            case BA_MISS: {
                // do nothing
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED, "Something is wrong with the balloon states.\n");
                break;
            }
        }
    }
    return ctx;
}

static bool o_balloons_is_outside(balloon_t * balloon) {
    return balloon->tgt.y + balloon->sim.h < 0 ||
           balloon->tgt.y > SCREEN_HEIGHT  ||
           balloon->tgt.x + balloon->sim.w < 0 ||
           balloon->tgt.x > SCREEN_WIDTH;
}
