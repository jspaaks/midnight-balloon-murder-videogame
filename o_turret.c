#include "o_turret.h"
#include "context.h"
#include "constants.h"
#include <SDL_rect.h>
#include <stdbool.h>

static double o_turret_max (double, double);
static double o_turret_min (double, double);
static double o_turret_clip (double);

static const SDL_Rect turret_src = {
    .x = 4,
    .y = 1,
    .w = 70,
    .h = 60,
};
static const SDL_Rect barrel_src = {
    .x = 4,
    .y = 68,
    .w = 55,
    .h = 12,
};
static const SDL_Rect flash_src = {
    .x = 166,
    .y = 63,
    .w = 30,
    .h = 22,
};

static const SDL_Rect turret_tgt = {
    .x = 180,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT - turret_src.h,
    .w = turret_src.w,
    .h = turret_src.h,
};
static const SDL_Rect barrel_tgt = {
    .x = turret_tgt.x + turret_src.w / 2,
    .y = turret_tgt.y + turret_src.w / 2 - barrel_src.h / 2,
    .w = barrel_src.w,
    .h = barrel_src.h,
};
static const SDL_Rect flash_tgt = {
    .x = barrel_tgt.x + barrel_src.w + 3,
    .y = barrel_tgt.y + barrel_src.h / 2 - flash_src.h / 2,
    .w = flash_src.w,
    .h = flash_src.h,
};

static const SDL_Point barrel_center = {
    .x = 0,
    .y = barrel_src.h / 2,
};
static const SDL_Point flash_center = {
    .x = -1 * (barrel_src.w + 3),
    .y = flash_src.h / 2,
};

static double barrel_speed = 17; // degrees per second
static bool is_shooting = false;

static double o_turret_clip(double v) {
    const double barrel_angle_min = -71;
    const double barrel_angle_max = -14;
    v = o_turret_max(v, barrel_angle_min);
    v = o_turret_min(v, barrel_angle_max);
    return v;
}

void o_turret_draw (ctx_t * ctx) {
    // turret base
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &turret_src, &turret_tgt);

    // turret barrel
    SDL_RenderCopyEx(ctx->renderer, ctx->spritesheet, &barrel_src,
                                                      &barrel_tgt,
                                                      ctx->barrel_angle,
                                                      &barrel_center,
                                                      SDL_FLIP_NONE);
    // muzzle flash
    if (is_shooting) {
        SDL_RenderCopyEx(ctx->renderer, ctx->spritesheet, &flash_src,
                                                          &flash_tgt,
                                                          ctx->barrel_angle,
                                                          &flash_center,
                                                          SDL_FLIP_NONE);
    }
}

ctx_t * o_turret_init (ctx_t * ctx) {
    ctx->barrel_angle = -55;
    return ctx;
}

static double o_turret_max(double a, double b) {
    return a > b ? a : b;
}

static double o_turret_min(double a, double b) {
    return a < b ? a : b;
}

ctx_t * o_turret_update (ctx_t * ctx) {
    int flags = ctx->keys[SDL_SCANCODE_W] |
                ctx->keys[SDL_SCANCODE_S] << 1;
    switch (flags) {
        case 1: {
            ctx->barrel_angle = o_turret_clip(ctx->barrel_angle + -1 * barrel_speed * ctx->dt);
            break;
        }
        case 2: {
            ctx->barrel_angle = o_turret_clip(ctx->barrel_angle + 1 * barrel_speed * ctx->dt);
            break;
        }
    }
    is_shooting = ctx->keys[SDL_SCANCODE_SPACE] == 1;
    return ctx;
}
