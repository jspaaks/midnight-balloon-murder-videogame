#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "types.h"
#include "constants.h"
#include "o_ground.h"

void o_ground_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.ground.r,
                                          ctx->colors.ground.g,
                                          ctx->colors.ground.b,
                                          ctx->colors.ground.a);
    SDL_RenderFillRect(ctx->renderer, &ctx->ground.tgt);
}

ctx_t * o_ground_init (ctx_t * ctx) {
    int h = GROUND_HEIGHT;
    ctx->ground.tgt = (SDL_Rect){
        .x = 0,
        .y = ctx->scene.tgt.h - h,
        .w = SCREEN_WIDTH,
        .h = h
    };
    return ctx;
}
