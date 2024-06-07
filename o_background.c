#include "SDL_pixels.h"
#include "SDL_log.h"
#include "types.h"
#include "o_background.h"

void o_background_draw (ctx_t * ctx) {
    if (ctx->resized) {
        int w;
        int h;
        SDL_GetWindowSize(ctx->window, &w,&h);
        SDL_Log("resized, now %d x %d", w, h);
        ctx->resized = false;
    }
    static SDL_Color bgcolor = { .r = 0, .g = 22, .b = 43, .a = 0 };
    SDL_SetRenderDrawColor(ctx->renderer, bgcolor.r,
                                          bgcolor.g,
                                          bgcolor.b,
                                          bgcolor.a);
    SDL_RenderClear(ctx->renderer);
}
