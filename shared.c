#include "types.h"
#include <SDL_render.h>

void shared_draw_background (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 22, 43, 0);
    SDL_RenderClear(ctx->renderer);
}
