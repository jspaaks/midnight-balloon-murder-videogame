#include "o_background.h"
#include "types.h"

void background_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 22, 43, 0);
    SDL_RenderClear(ctx->renderer);
}
