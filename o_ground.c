#include "o_ground.h"
#include "constants.h"

static const SDL_Rect rect = {
    .x = 0,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = SCREEN_WIDTH,
    .h = GROUND_HEIGHT,
};

void ground_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 11, 1, 26, 0);
    SDL_RenderFillRect(ctx->renderer, &rect);
}
