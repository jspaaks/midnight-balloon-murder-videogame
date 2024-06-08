#include "SDL_pixels.h"
#include "SDL_log.h"
#include "types.h"
#include "o_background.h"

void o_background_draw (ctx_t * ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 0);
    SDL_RenderClear(ctx->renderer);
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.bg.r,
                                          ctx->colors.bg.g,
                                          ctx->colors.bg.b,
                                          ctx->colors.bg.a);
    SDL_RenderFillRect(ctx->renderer, &ctx->scene.tgt);
}
