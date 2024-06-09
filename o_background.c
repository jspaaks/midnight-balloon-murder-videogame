#include "SDL_render.h"
#include "types.h"
#include "o_background.h"

void o_background_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 0);
    SDL_RenderClear(ctx->renderer);
}
