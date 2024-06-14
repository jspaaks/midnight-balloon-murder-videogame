#include <stdio.h>
#include <assert.h>
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "types.h"
#include "o_flash.h"
#include "o_scene.h"

void o_flash_draw (ctx_t * ctx) {
    if (ctx->flash.show) {
        SDL_Rect tgt = sim2tgt(ctx->scene, ctx->flash.sim);
        SDL_Point pivot_offset = (SDL_Point) {
            .x = (int) (ctx->flash.sim2.pivot_offset.x * ctx->scene.scale),
            .y = (int) (ctx->flash.sim2.pivot_offset.y * ctx->scene.scale),
        };
        SDL_RenderCopyEx(ctx->renderer, ctx->spritesheet, &ctx->flash.src,
                                                          &tgt,
                                                          ctx->barrel.sim2.angle,
                                                          &pivot_offset,
                                                          SDL_FLIP_NONE);
    }
}

void o_flash_init (ctx_t * ctx) {
    assert(ctx->barrel.sim.x != 0 && "barrel needs to be initialized before flash");
    float h = 21;
    float w = 30;
    float loffset = (ctx->barrel.sim.w + 2);
    SDL_Rect src = {
        .h = h,
        .w = w,
        .x = 166,
        .y = 63,
    };
    SDL_FRect sim = {
        .h = h,
        .w = w,
        .x = ctx->barrel.sim2.pivot.x + loffset,
        .y = ctx->barrel.sim2.pivot.y - (h - 1) / 2,
    };
    ctx->flash = (flash_t) {
        .show = false,
        .sim = sim,
        .sim2 = {
            .pivot_offset = (SDL_FPoint) {
                .x = -1 * loffset,
                .y = (h - 1) / 2,
            },
        },
        .src = src,
    };
}

void o_flash_update (ctx_t * ctx) {
    static Uint64 timeout = 25;
    ctx->flash.show = SDL_GetTicks64() < ctx->tspawn_latestbullet  + timeout;
}
