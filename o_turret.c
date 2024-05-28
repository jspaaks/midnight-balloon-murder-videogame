#include "o_turret.h"
#include "types.h"
#include "constants.h"
#include <SDL_rect.h>

static double max (double, double);
static double min (double, double);
static double clip (double);

static const dims_t turret = {
    .w = 70,
    .h = 60
};

static const dims_t barrel = {
    .w = 45,
    .h = 12
};

static const SDL_Rect turret_src = {
    .x = 4,
    .y = 1,
    .w = turret.w,
    .h = turret.h,
};

static const SDL_Rect turret_tgt = {
    .x = 180,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT - turret.h,
    .w = turret.w,
    .h = turret.h,
};

static const SDL_Rect barrel_src = {
    .x = 4,
    .y = 68,
    .w = barrel.w,
    .h = barrel.h,
};

static const SDL_Rect barrel_tgt = {
    .x = 180 + turret.w - 20,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT - turret.h + turret.w / 2 - barrel.h / 2,
    .w = barrel.w,
    .h = barrel.h,
};

static const SDL_Point barrel_center = {
    .x = turret.w / -2 + 20,
    .y = barrel.h / 2,
};

double barrel_angle = -55;
double barrel_speed = 2; // degrees per second

void turret_draw (ctx_t * ctx) {
    SDL_RenderCopy(ctx->renderer, ctx->sprites, &turret_src, &turret_tgt);
    SDL_RenderCopyEx(ctx->renderer, ctx->sprites, &barrel_src,
                                                  &barrel_tgt,
                                                  barrel_angle,
                                                  &barrel_center,
                                                  SDL_FLIP_NONE);
}

void turret_update (SDL_Event * event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_w) {
            barrel_angle = clip(barrel_angle + -1 * barrel_speed);
            // TODO take into account integration of barrel_speed over time
        }
        if (event->key.keysym.sym == SDLK_s) {
            barrel_angle = clip(barrel_angle + 1 * barrel_speed);
            // TODO take into account integration of barrel_speed over time
        }
    }
}


static double max(double a, double b) {
    return a > b ? a : b;
}

static double min(double a, double b) {
    return a < b ? a : b;
}

static double clip(double v) {
    fprintf(stdout, "%f\n", v);
    const double barrel_angle_min = -62;
    const double barrel_angle_max = -24;
    v = max(v, barrel_angle_min);
    v = min(v, barrel_angle_max);
    return v;
}
