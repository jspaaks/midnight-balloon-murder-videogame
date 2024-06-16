#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_log.h"
#include "scene.h"
#include "types.h"

scene_t scene_init(void) {
    float h = 720.0;
    float w = 1280.0;
    return (scene_t) {
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
}

void scene_update (ctx_t * ctx, SDL_Renderer * renderer, scene_t * scene) {
    if (ctx->resized) {
        int w0;
        int h0;
        SDL_GetRendererOutputSize(renderer, &w0, &h0);
        float w = w0 < scene->sim.w ? scene->sim.w : (float) (w0);
        float h = h0 < scene->sim.h ? scene->sim.h : (float) (h0);
        float ratio = w / h;
        if (ratio > scene->ratio) {
            // -- too wide
            scene->tgt.h = h;
            scene->tgt.w = (int)(scene->ratio * h);
            scene->tgt.x = (int) ((w - scene->tgt.w) / 2);
            scene->tgt.y = 0;
        } else if (ratio < scene->ratio) {
            // -- too tall
            scene->tgt.w = w;
            scene->tgt.h = (int)(w / scene->ratio);
            scene->tgt.x = 0;
            scene->tgt.y = (int) ((h - scene->tgt.h) / 2);
        } else {
            // -- correct aspect ratio
            scene->tgt.w = (int) (w);
            scene->tgt.h = (int) (h);
            scene->tgt.x = 0;
            scene->tgt.y = 0;
        }
        scene->scale = scene->tgt.w / scene->sim.w;
        ctx->resized = false;
    }
}

SDL_Rect sim2tgt(scene_t scene, SDL_FRect sim) {
    return (SDL_Rect){
        .x = scene.tgt.x + (int)(sim.x * scene.scale),
        .y = scene.tgt.y + (int)(sim.y * scene.scale),
        .w = (int)(sim.w * scene.scale),
        .h = (int)(sim.h * scene.scale),
    };
}
