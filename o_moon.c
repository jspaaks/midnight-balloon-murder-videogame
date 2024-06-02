#include "types.h"
#include "constants.h"
#include <SDL_rect.h>

static const SDL_Rect src = {
    .x = 75,
    .y = 1,
    .w = 90,
    .h = 90,
};

static const SDL_Rect tgt = {
    .x = SCREEN_WIDTH - 90 - 40,
    .y = 40,
    .w = 90,
    .h = 90,
};

void o_moon_draw (ctx_t * ctx) {
    SDL_RenderCopy(ctx->renderer, ctx->spritesheet, &src, &tgt);
}
