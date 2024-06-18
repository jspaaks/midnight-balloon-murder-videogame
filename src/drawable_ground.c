#include "drawable_ground.h"
#include "scene.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "types.h"
#include <assert.h>

void drawable_groundrawable_draw (SDL_Renderer * renderer, colors_t colors, scene_t scene, groundrawable_t ground) {
    SDL_Rect tgt = sim2tgt(scene, ground.sim);
    SDL_SetRenderDrawColor(renderer, colors.ground.r, colors.ground.g, colors.ground.b,
                           colors.ground.a);
    SDL_RenderFillRect(renderer, &tgt);
}

groundrawable_t drawable_groundrawable_init (scene_t scene) {
    assert(scene.tgt.w != 0 && "scene needs to be initialized before ground");
    float h = 100;
    return (groundrawable_t){
        .sim =
            (SDL_FRect){
                        .h = h,
                        .w = scene.sim.w,
                        .x = 0,
                        .y = scene.sim.h - h,
                        },
    };
}
