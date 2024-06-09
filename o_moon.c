#include "SDL_rect.h"
#include "types.h"
#include "o_moon.h"

void o_moon_draw (ctx_t * ctx) {
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &ctx->moon.src, &ctx->moon.tgt);
}

ctx_t * o_moon_init (ctx_t * ctx) {
    unsigned int x = 75;
    unsigned int y = 1;
    unsigned int w = 90;
    unsigned int h = 90;
    ctx->moon = (moon_t){
        .src = (SDL_Rect){
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        },
        .tgt = (SDL_Rect){
            .x = ctx->scene.tgt.w - w - 40,
            .y = ctx->scene.tgt.y + 40,
            .w = w,
            .h = h,
        },
    };
    return ctx;
}
