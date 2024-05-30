#include "o_ground.h"
#include "constants.h"
#include "colors.h"

static const SDL_Rect rect = {
    .x = 0,
    .y = SCREEN_HEIGHT - GROUND_HEIGHT,
    .w = SCREEN_WIDTH,
    .h = GROUND_HEIGHT,
};

void ground_draw (ctx_t * ctx) {
    static rgba_t ground = { .r = 11, .g = 1, .b = 26, .a = 0 };
    SDL_SetRenderDrawColor(ctx->renderer, ground.r,
                                          ground.g,
                                          ground.b,
                                          ground.a);
    SDL_RenderFillRect(ctx->renderer, &rect);
}
