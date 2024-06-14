#include <assert.h>
#include "SDL_scancode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "types.h"
#include "o_barrel.h"
#include "o_scene.h"

static float o_barrel_max (float, float);
static float o_barrel_min (float, float);
static float o_barrel_clip (float);

static float o_barrel_clip(float v) {
    const float barrel_angle_min = -71;
    const float barrel_angle_max = -18;
    v = o_barrel_max(v, barrel_angle_min);
    v = o_barrel_min(v, barrel_angle_max);
    return v;
}

void o_barrel_draw (ctx_t * ctx) {
    SDL_Rect tgt = sim2tgt(ctx->scene, ctx->barrel.sim);
    SDL_Point pivot_offset = (SDL_Point) {
        .x = (int) (ctx->barrel.sim2.pivot_offset.x * ctx->scene.scale),
        .y = (int) (ctx->barrel.sim2.pivot_offset.y * ctx->scene.scale),
    };
    SDL_RenderCopyEx(ctx->renderer, ctx->spritesheet, &ctx->barrel.src,
                                                      &tgt,
                                                      ctx->barrel.sim2.angle,
                                                      &pivot_offset,
                                                      SDL_FLIP_NONE);
}

void o_barrel_init (ctx_t * ctx) {
    assert(ctx->turret.sim.x != 0 && "turret needs to be initialized before barrel");
    SDL_Rect src = {
        .h = 11,
        .w = 55,
        .x = 4,
        .y = 68,
    };
    SDL_FRect sim = {
        .h = src.h,
        .w = src.w,
        .x = ctx->turret.sim.x + (ctx->turret.sim.w - 1) / 2,
        .y = ctx->turret.sim.y + (ctx->turret.sim.w - 1) / 2 - (src.h - 1) / 2,
    };
    ctx->barrel = (barrel_t) {
        .sim = {
            .h = sim.h,
            .w = sim.w,
            .x = sim.x,
            .y = sim.y,
        },
        .sim2 = {
            .angle = -25.0,
            .length = sim.w,
            .pivot = (SDL_FPoint) {
                .x = ctx->turret.sim.x + ctx->turret.sim.w / 2,
                .y = ctx->turret.sim.y + ctx->turret.sim.w / 2,
            },
            .pivot_offset = (SDL_FPoint) {
                .x = 0,
                .y = (int) sim.h / 2,
            },
            .speed = 17,
        },
        .src = src,
    };
}

static float o_barrel_max(float a, float b) {
    return a > b ? a : b;
}

static float o_barrel_min(float a, float b) {
    return a < b ? a : b;
}

void o_barrel_update (ctx_t * ctx) {
    int flags = ctx->keys[SDL_SCANCODE_W] |
                ctx->keys[SDL_SCANCODE_S] << 1;
    switch (flags) {
        case 1: {
            ctx->barrel.sim2.angle = o_barrel_clip(ctx->barrel.sim2.angle + -1 * ctx->barrel.sim2.speed * ctx->dt.frame);
            break;
        }
        case 2: {
            ctx->barrel.sim2.angle = o_barrel_clip(ctx->barrel.sim2.angle + 1 * ctx->barrel.sim2.speed * ctx->dt.frame);
            break;
        }
    }
}
