#include "o_balloons.h"
#include "context.h"
#include "constants.h"


static const SDL_Rect yellow = {
    .x = 166,
    .y = 1,
    .w = 12,
    .h = 16,
};
static const SDL_Rect orange = {
    .x = 184,
    .y = 1,
    .w = 9,
    .h = 12,
};
static const SDL_Rect red = {
    .x = 184,
    .y = 20,
    .w = 6,
    .h = 7,
};

static balloon_t balloon = {
    .x = 3 * SCREEN_WIDTH / 4,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = yellow.w,
    .h = yellow.h,
    .u = 0,
    .v = -2,
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

static double dt = 0.01;

void balloons_draw (ctx_t * ctx) {
    if (balloon.state == AIRBORNE) {
        SDL_RenderCopy(ctx->renderer, ctx->spritesheet, balloon.src, &balloon.tgt);
    }
}

void balloons_update (void) {
    balloon.x += balloon.u * dt;
    balloon.y += balloon.v * dt;
    balloon.tgt.x = (int) balloon.x;
    balloon.tgt.y = (int) balloon.y;
    if (balloon.tgt.y + balloon.h < 0 || balloon.tgt.y > SCREEN_HEIGHT || balloon.tgt.x + balloon.w < 0 || balloon.tgt.x > SCREEN_WIDTH ) {
        balloon.state = MISS;
    }
}
