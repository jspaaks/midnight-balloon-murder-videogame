#include "scene.h"
#include "SDL_rect.h"

ctx_t * scene_init(ctx_t * ctx) {
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int w = 1280;
    unsigned int h = 720;
    ctx->scene = (scene_t) {
        .sim = (SDL_FRect) {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        },
        .tgt = (SDL_Rect) {
            .x = x,
            .y = y,
            .w = w,
            .h = h,
        }
    };
    ctx->resized = true;
    return ctx;
}

ctx_t * s_scene_update (ctx_t * ctx, state_t ** state) {
    if (ctx->scene.resized) {
        int w;
        int h;
        SDL_GetRendererOutputSize(ctx->renderer, &w, &h);
        float actual_ratio = (float) (w) / h;
        float desired_ratio = ctx->scene.sim.w / ctx->scene.sim.h;
        if (actual_ratio > desired_ratio) {
            SDL_Log("%d, %d -- too wide\n", w, h);
        } else if (actual_ratio < desired_ratio) {
            SDL_Log("%d, %d -- too tall\n", w, h);
        } else {
            SDL_Log("%d, %d -- correct aspect ratio\n", w, h);
        }
    }
}
