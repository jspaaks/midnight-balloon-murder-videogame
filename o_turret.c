#include "SDL_render.h"
#include "SDL_rect.h"
#include "types.h"
#include "constants.h"
#include "o_turret.h"

void o_turret_draw (ctx_t * ctx) {
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &ctx->turret.src, &ctx->turret.tgt);
}

ctx_t * o_turret_init (ctx_t * ctx) {
    float w = 69;
    float h = 47;
    float x = 180;
    float y = SCREEN_HEIGHT - GROUND_HEIGHT - h;
    ctx->turret = (turret_t){
        .sim = (SDL_FRect) {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        },
        .src = (SDL_Rect) {
            .x = 4,
            .y = 1,
            .w = w,
            .h = h,
        },
        .tgt = (SDL_Rect) {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        },
    };
    return ctx;
}

ctx_t * o_turret_update (ctx_t * ctx) {
    return ctx;
}
