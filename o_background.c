#include "SDL_render.h"
#include "types.h"
#include "o_background.h"

void o_background_draw (SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}
