#include "mbm/drawable_turret.h"
#include "mbm/scene.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "mbm/types.h"
#include <assert.h>

void drawable_turret_draw (SDL_Renderer * renderer, SDL_Texture * spritesheet, scene_t scene,
                           turret_t turret) {
    SDL_Rect tgt = sim2tgt(scene, turret.sim);
    SDL_RenderCopy(renderer, spritesheet, &turret.src, &tgt);
}

turret_t drawable_turret_init (scene_t scene, ground_t ground) {
    assert(ground.sim.w != 0 && "ground needs to be initialized before turret");
    float h = 47;
    SDL_FRect sim = {
        .h = h,
        .w = 69,
        .x = 180,
        .y = scene.sim.h - ground.sim.h - h,
    };
    return (turret_t){
        .sim = sim,
        .src =
            (SDL_Rect){
                       .h = 47,
                       .w = 69,
                       .x = 4,
                       .y = 1,
                       },
    };
}
