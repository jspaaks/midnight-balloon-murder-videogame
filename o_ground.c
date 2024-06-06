#include "SDL_pixels.h"
#include "types.h"
#include "constants.h"
#include "o_ground.h"

static const SDL_Rect rect = {
    .x = 0,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = SCREEN_WIDTH,
    .h = GROUND_HEIGHT,
};

void o_ground_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.ground.r,
                                          ctx->colors.ground.g,
                                          ctx->colors.ground.b,
                                          ctx->colors.ground.a);
    SDL_RenderFillRect(ctx->renderer, &rect);
}
