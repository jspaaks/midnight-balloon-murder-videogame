#include "mbm/drawable_background.h"
#include "SDL_render.h"
#include "mbm/types.h"

void drawable_background_draw (SDL_Renderer * renderer, colors_t colors, scene_t scene) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, colors.bg.r, colors.bg.g, colors.bg.b, colors.bg.a);
    SDL_RenderFillRect(renderer, &scene.tgt);
}
