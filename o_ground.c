#include <assert.h>
#include "SDL_render.h"
#include "SDL_rect.h"
#include "types.h"
#include "o_ground.h"

void o_ground_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.ground.r,
                                          ctx->colors.ground.g,
                                          ctx->colors.ground.b,
                                          ctx->colors.ground.a);
    SDL_RenderFillRect(ctx->renderer, &ctx->ground.tgt);
}

ctx_t * o_ground_init (ctx_t * ctx) {
    assert(ctx->scene.tgt.w != 0 && "scene needs to be initialized before ground");
    unsigned int h = 100;
    unsigned int x = 0;
    unsigned int w = ctx->scene.tgt.w;
    unsigned int y = ctx->scene.tgt.h - h;
    ctx->ground.sim = (SDL_FRect) {
        .h = h,
        .w = w,
        .x = x,
        .y = y,
    };
    ctx->ground.tgt = (SDL_Rect) {
        .h = ctx->ground.sim.h,
        .w = ctx->ground.sim.w,
        .x = ctx->ground.sim.x,
        .y = ctx->ground.sim.y,
    };
    return ctx;
}
