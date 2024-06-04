#include <assert.h>
#include "SDL_scancode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "types.h"
#include "o_barrel.h"

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
    SDL_RenderCopyEx(ctx->renderer, ctx->spritesheet, &ctx->barrel.src,
                                                      &ctx->barrel.tgt,
                                                      ctx->barrel.angle,
                                                      &ctx->barrel.pivot_offset,
                                                      SDL_FLIP_NONE);
}

ctx_t * o_barrel_init (ctx_t * ctx) {
    assert(ctx->turret.tgt.x != 0 && "turret needs to be initialized before barrel");
    float w = 55.;
    float h = 11.;
    float x = ctx->turret.sim.x + (ctx->turret.sim.w - 1) / 2;
    float y = ctx->turret.sim.y + (ctx->turret.sim.w - 1) / 2 - (h - 1) / 2;
    ctx->barrel = (barrel_t) {
        .angle = -55.0,
        .length = w,
        .speed = 17,
        .pivot = (SDL_FPoint) {
            .x = ctx->turret.sim.x + ctx->turret.sim.w / 2,
            .y = ctx->turret.sim.y + ctx->turret.sim.w / 2,
        },
        .sim = (SDL_FRect) {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        },
        .pivot_offset = (SDL_Point) {
            .x = 0,
            .y = (int) h / 2,
        },
        .src = (SDL_Rect) {
            .x = 4,
            .y = 68,
            .w = w,
            .h = h,
        },
        .tgt = (SDL_Rect) {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        }
    };
    return ctx;
}

static float o_barrel_max(float a, float b) {
    return a > b ? a : b;
}

static float o_barrel_min(float a, float b) {
    return a < b ? a : b;
}

ctx_t * o_barrel_update (ctx_t * ctx) {
    int flags = ctx->keys[SDL_SCANCODE_W] |
                ctx->keys[SDL_SCANCODE_S] << 1;
    switch (flags) {
        case 1: {
            ctx->barrel.angle = o_barrel_clip(ctx->barrel.angle + -1 * ctx->barrel.speed * ctx->dt);
            break;
        }
        case 2: {
            ctx->barrel.angle = o_barrel_clip(ctx->barrel.angle + 1 * ctx->barrel.speed * ctx->dt);
            break;
        }
    }
    return ctx;
}
