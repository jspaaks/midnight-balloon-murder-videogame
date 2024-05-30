#include <stdlib.h>
#include "o_balloons.h"
#include "context.h"
#include "constants.h"
#include "levels.h"

static const SDL_Rect yellow = {
    .x = 166,
    .y = 1,
    .w = 12,
    .h = 16,
};
//static const SDL_Rect orange = {
//    .x = 184,
//    .y = 1,
//    .w = 9,
//    .h = 12,
//};
//static const SDL_Rect red = {
//    .x = 184,
//    .y = 20,
//    .w = 6,
//    .h = 7,
//};

static bool is_outside(balloon_t *);

void o_balloons_draw (ctx_t * ctx) {
    for (int i = 0; i < ctx->level->nballoons; i++) {
        if (ctx->balloons[i].state == AIRBORNE) {
            SDL_RenderCopy(ctx->renderer, ctx->spritesheet, ctx->balloons[i].src, &ctx->balloons[i].tgt);
        }
    }
}

balloon_t * o_balloons_init (ctx_t * ctx) {
    balloon_t * balloons = malloc(ctx->level->nballoons * sizeof(balloon_t));

    balloon_t balloon = {
        .x = 3 * SCREEN_WIDTH / 4,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT,
        .w = yellow.w,
        .h = yellow.h,
        .u = 0.0,
        .v = -30.0,
        .value = 5,
        .state = AIRBORNE,
        .src = &yellow,
        .tgt = {
            .x = 3 * SCREEN_WIDTH / 4,
            .y = SCREEN_HEIGHT - GROUND_HEIGHT,
            .w = yellow.w,
            .h = yellow.h,
        },
    };
    balloon_t * b = balloons;
    for (int i = 0; i < ctx->level->nballoons; i++) {
        *b = balloon;
        b->x += 10 * i;
        b->tgt.x += 10 * i;
        b++;
    }
    return balloons;
}

void o_balloons_update (ctx_t * ctx) {
    for (int i = 0; i < ctx->level->nballoons; i++) {
        switch (ctx->balloons[i].state) {
            case PRESPAWN: {
                break;
            }
            case AIRBORNE: {
                ctx->balloons[i].x += ctx->balloons[i].u * ctx->dt;
                ctx->balloons[i].y += ctx->balloons[i].v * ctx->dt;
                ctx->balloons[i].tgt.x = (int) ctx->balloons[i].x;
                ctx->balloons[i].tgt.y = (int) ctx->balloons[i].y;
                if (is_outside(&ctx->balloons[i])) {
                    ctx->balloons[i].state = MISS;
                }
                break;
            }
            case HIT: {
                break;
            }
            case MISS: {
                break;
            }
            default: {
                fprintf(stderr, "Something is wrong with the balloon states.\n");
                break;
            }
        }
    }
}

static bool is_outside(balloon_t * balloon) {
    return balloon->tgt.y + balloon->h < 0 ||
           balloon->tgt.y > SCREEN_HEIGHT  ||
           balloon->tgt.x + balloon->w < 0 ||
           balloon->tgt.x > SCREEN_WIDTH;
}
