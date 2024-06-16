#include <assert.h>
#include "SDL_render.h"
#include "SDL_rect.h"
#include "scene.h"
#include "types.h"
#include "o_ground.h"

void o_ground_draw (SDL_Renderer * renderer, colors_t colors, scene_t scene, ground_t ground) {
    SDL_Rect tgt = sim2tgt(scene, ground.sim);
    SDL_SetRenderDrawColor(renderer, colors.ground.r,
                                     colors.ground.g,
                                     colors.ground.b,
                                     colors.ground.a);
    SDL_RenderFillRect(renderer, &tgt);
}

ground_t o_ground_init (scene_t scene) {
    assert(scene.tgt.w != 0 && "scene needs to be initialized before ground");
    float h = 100;
    return (ground_t) {
        .sim = (SDL_FRect) {
            .h = h,
            .w = scene.sim.w,
            .x = 0,
            .y = scene.sim.h - h,
        },
    };
}
