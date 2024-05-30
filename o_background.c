#include "o_background.h"
#include "context.h"
#include "colors.h"

void background_draw (ctx_t * ctx) {
    static rgba_t bgcolor = { .r = 0, .g = 22, .b = 43, .a = 0 };
    SDL_SetRenderDrawColor(ctx->renderer, bgcolor.r,
                                          bgcolor.g,
                                          bgcolor.b,
                                          bgcolor.a);
    SDL_RenderClear(ctx->renderer);
}
