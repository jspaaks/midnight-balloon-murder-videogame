#include "o_turret.h"
#include "types.h"
#include "constants.h"
#include <SDL_rect.h>
#include <stdbool.h>

static double max (double, double);
static double min (double, double);
static double clip (double);

static const dims_t turret = {
    .w = 70,
    .h = 60
};

static const dims_t barrel = {
    .w = 55,
    .h = 12
};
static const dims_t flash = {
    .w = 30,
    .h = 22
};

static const SDL_Rect turret_src = {
    .x = 4,
    .y = 1,
    .w = turret.w,
    .h = turret.h,
};
static const SDL_Rect barrel_src = {
    .x = 4,
    .y = 68,
    .w = barrel.w,
    .h = barrel.h,
};
static const SDL_Rect flash_src = {
    .x = 166,
    .y = 63,
    .w = flash.w,
    .h = flash.h,
};

static const SDL_Rect turret_tgt = {
    .x = 180,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT - turret.h,
    .w = turret.w,
    .h = turret.h,
};
static const SDL_Rect barrel_tgt = {
    .x = turret_tgt.x + turret.w / 2,
    .y = turret_tgt.y + turret.w / 2 - barrel.h / 2,
    .w = barrel.w,
    .h = barrel.h,
};
static const SDL_Rect flash_tgt = {
    .x = barrel_tgt.x + barrel.w + 3,
    .y = barrel_tgt.y + barrel.h / 2 - flash.h / 2,
    .w = flash.w,
    .h = flash.h,
};

static const SDL_Point barrel_center = {
    .x = 0,
    .y = barrel.h / 2,
};
static const SDL_Point flash_center = {
    .x = -1 * (barrel.w + 3),
    .y = flash.h / 2,
};

static double barrel_angle = -55;
static double barrel_speed = 2; // degrees per second
static bool is_shooting = false;

void turret_draw (ctx_t * ctx) {
    // turret base
    SDL_RenderCopy(ctx->renderer, ctx->sprites, &turret_src, &turret_tgt);

    // turret barrel
    SDL_RenderCopyEx(ctx->renderer, ctx->sprites, &barrel_src,
                                                  &barrel_tgt,
                                                  barrel_angle,
                                                  &barrel_center,
                                                  SDL_FLIP_NONE);
    // muzzle flash
    if (is_shooting) {
        SDL_RenderCopyEx(ctx->renderer, ctx->sprites, &flash_src,
                                                    &flash_tgt,
                                                    barrel_angle,
                                                    &flash_center,
                                                    SDL_FLIP_NONE);
    }
}

void turret_update (ctx_t * ctx) {
    int flags = ctx->keys[SDL_SCANCODE_W] |
                ctx->keys[SDL_SCANCODE_S] << 1;
    double dt = 0.01;
    switch (flags) {
        case 1: {
            barrel_angle = clip(barrel_angle + -1 * barrel_speed * dt);
            break;
        }
        case 2: {
            barrel_angle = clip(barrel_angle + 1 * barrel_speed * dt);
            break;
        }
    }
    is_shooting = ctx->keys[SDL_SCANCODE_SPACE] == 1;
}


static double max(double a, double b) {
    return a > b ? a : b;
}

static double min(double a, double b) {
    return a < b ? a : b;
}

static double clip(double v) {
    const double barrel_angle_min = -62;
    const double barrel_angle_max = -24;
    v = max(v, barrel_angle_min);
    v = min(v, barrel_angle_max);
    return v;
}
