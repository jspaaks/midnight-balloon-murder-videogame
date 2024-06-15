#include <assert.h>
#include "SDL_render.h"
#include "SDL_rect.h"
#include "types.h"
#include "o_ground.h"
#include "o_scene.h"

void o_ground_draw (SDL_Renderer * renderer, scene_t scene, colors_t colors, ground_t ground) {
    SDL_Rect tgt = sim2tgt(scene, ground.sim);
    SDL_SetRenderDrawColor(renderer, colors.ground.r,
                                     colors.ground.g,
                                     colors.ground.b,
                                     colors.ground.a);
    SDL_RenderFillRect(renderer, &tgt);
}

void o_ground_init (scene_t scene, ground_t * ground) {
    assert(scene.tgt.w != 0 && "scene needs to be initialized before ground");
    float h = 100;
    ground->sim = (SDL_FRect) {
        .h = h,
        .w = scene.sim.w,
        .x = 0,
        .y = scene.sim.h - h,
    };
}
