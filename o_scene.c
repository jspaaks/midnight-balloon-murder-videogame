#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_log.h"
#include "o_scene.h"
#include "types.h"

ctx_t * o_scene_init(ctx_t * ctx) {
    float h = 720.0;
    float w = 1280.0;
    ctx->scene = (scene_t) {
        .sim = {
            .h = h,
            .w = w,
            .x = 0.0,
            .y = 0.0,
        },
        .ratio = w / h,
        .scale = 1.0,
        .tgt = (SDL_Rect){
            .h = (int) (h),
            .w = (int) (w),
            .x = 0.0,
            .y = 0.0,
        },
    };
    ctx->resized = true;
    return ctx;
}

void o_scene_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.bg.r,
                                          ctx->colors.bg.g,
                                          ctx->colors.bg.b,
                                          ctx->colors.bg.a);
    SDL_RenderFillRect(ctx->renderer, &ctx->scene.tgt);
}

ctx_t * o_scene_update (ctx_t * ctx) {
    if (ctx->scene.resized) {
        int w0;
        int h0;
        SDL_GetRendererOutputSize(ctx->renderer, &w0, &h0);
        float w = (float) (w0);
        float h = (float) (h0);
        float ratio = w / h;
        if (ratio > ctx->scene.ratio) {
            SDL_Log("%d, %d -- too wide\n", w0, h0);
            ctx->scene.tgt.h = h;
            ctx->scene.tgt.w = (int)(ctx->scene.ratio * h);
            ctx->scene.tgt.x = (int) ((w - ctx->scene.tgt.w) / 2);
            ctx->scene.tgt.y = 0;
        } else if (ratio < ctx->scene.ratio) {
            SDL_Log("%d, %d -- too tall\n", w0, h0);
            ctx->scene.tgt.w = w;
            ctx->scene.tgt.h = (int)(w / ctx->scene.ratio);
            ctx->scene.tgt.x = 0;
            ctx->scene.tgt.y = (int) ((h - ctx->scene.tgt.h) / 2);
        } else {
            SDL_Log("%d, %d -- correct aspect ratio\n", w0, h0);
            ctx->scene.tgt.w = (int) (w);
            ctx->scene.tgt.h = (int) (h);
            ctx->scene.tgt.x = 0;
            ctx->scene.tgt.y = 0;
        }
        ctx->scene.scale = ctx->scene.tgt.w / ctx->scene.sim.w;
        ctx->resized = false;
    }
    return ctx;
}

SDL_Rect sim2tgt(scene_t scene, SDL_FRect sim) {
    return (SDL_Rect){
        .x = scene.tgt.x + (int)(sim.x * scene.scale),
        .y = scene.tgt.y + (int)(sim.y * scene.scale),
        .w = (int)(sim.w * scene.scale),
        .h = (int)(sim.h * scene.scale),
    };
}
