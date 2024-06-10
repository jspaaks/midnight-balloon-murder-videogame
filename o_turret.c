#include <assert.h>
#include "SDL_render.h"
#include "SDL_rect.h"
#include "types.h"
#include "o_turret.h"
#include "o_scene.h"

void o_turret_draw (ctx_t * ctx) {
    SDL_Rect tgt = sim2tgt(ctx->scene, ctx->turret.sim);
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &ctx->turret.src, &tgt);
}

ctx_t * o_turret_init (ctx_t * ctx) {
    assert(ctx->ground.sim.w != 0 && "ground needs to be initialized before turret");
    float h = 47;
    SDL_FRect sim = {
        .h = h,
        .w = 69,
        .x = 180,
        .y = ctx->scene.sim.h - ctx->ground.sim.h - h,
    };
    ctx->turret = (turret_t){
        .sim = sim,
        .src = (SDL_Rect) {
            .h = 47,
            .w = 69,
            .x = 4,
            .y = 1,
        },
    };
    return ctx;
}

ctx_t * o_turret_update (ctx_t * ctx) {
    return ctx;
}
