#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "types.h"
#include "o_flash.h"

void o_flash_draw (ctx_t * ctx) {
    if (ctx->flash.show) {
        SDL_RenderCopyEx(ctx->renderer, ctx->spritesheet, &ctx->flash.src,
                                                          &ctx->flash.tgt,
                                                          ctx->barrel.angle,
                                                          &ctx->flash.pivot_offset,
                                                          SDL_FLIP_NONE);
    }
}

ctx_t * o_flash_init (ctx_t * ctx) {
    assert(ctx->barrel.tgt.x != 0 && "barrel needs to be initialized before flash");
    float h = 21;
    float w = 30;
    float loffset = (ctx->barrel.tgt.w + 2);
    float x = ctx->barrel.pivot.x + loffset;
    float y = ctx->barrel.pivot.y - (h - 1) / 2;
    ctx->flash = (flash_t) {
        .pivot_offset = (SDL_Point) {
            .x = -1 * loffset,
            .y = (h - 1) / 2,
        },
        .show = false,
        .sim = (SDL_FRect) {
            .h = h,
            .w = w,
            .x = x,
            .y = y,
        },
        .src = (SDL_Rect) {
            .h = h,
            .w = w,
            .x = 166,
            .y = 63,
        },
        .tgt = (SDL_Rect) {
            .h = h,
            .w = w,
            .x = x,
            .y = y,
        },
    };
    return ctx;
}

ctx_t * o_flash_update (ctx_t * ctx) {
    static Uint64 timeout = 25;
    ctx->flash.show = SDL_GetTicks64() < ctx->tspawn_latestbullet  + timeout;
    return ctx;
}
