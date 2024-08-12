#include "mbm/drawable_moon.h"
#include "mbm/scene.h"
#include "SDL_rect.h"
#include "mbm/types.h"

void drawable_moon_draw (SDL_Renderer * renderer, SDL_Texture * spritesheet, scene_t scene,
                         moon_t moon) {
    SDL_Rect tgt = sim2tgt(scene, moon.sim);
    SDL_RenderCopy(renderer, spritesheet, &moon.src, &tgt);
}

moon_t drawable_moon_init (scene_t scene) {
    return (moon_t){
        .src = (SDL_Rect){
            .x = 75,
            .y = 1,
            .w = 90,
            .h = 90,
        },
        .sim = {
            .x = scene.sim.w - 130,
            .y = scene.sim.y + 40,
            .w = 90,
            .h = 90,
        },
    };
}
