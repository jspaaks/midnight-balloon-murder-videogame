#include "SDL_rect.h"
#include "types.h"
#include "o_moon.h"

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
        .tgt = (SDL_Rect){
            .x = ctx->scene.tgt.w - 90 - 40,
            .y = 40,
            .w = 90,
            .h = 90,
        },
    };
    return ctx;
}
