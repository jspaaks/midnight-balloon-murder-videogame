#include "SDL_rect.h"
#include "types.h"
#include "o_moon.h"
#include "o_scene.h"

void o_moon_draw (ctx_t * ctx) {
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &ctx->moon.src, &ctx->moon.tgt);
}

ctx_t * o_moon_init (ctx_t * ctx) {
    ctx->moon = (moon_t){
        .src = (SDL_Rect){
            .x = 75,
            .y = 1,
            .w = 90,
            .h = 90,
        },
        .sim = {
            .x = ctx->scene.sim.w - 130,
            .y = ctx->scene.sim.y + 40,
            .w = 90,
            .h = 90,
        },
    };
    ctx->moon.tgt = sim2tgt(ctx->scene, ctx->moon.sim);
    return ctx;
}

ctx_t * o_moon_update (ctx_t * ctx) {
    ctx->moon.tgt = sim2tgt(ctx->scene, ctx->moon.sim);
    return ctx;
}
