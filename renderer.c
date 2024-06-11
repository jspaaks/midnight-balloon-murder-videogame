#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_hints.h"
#include "renderer.h"
#include "types.h"


ctx_t * renderer_deinit (ctx_t * ctx) {
    SDL_DestroyRenderer(ctx->renderer);
    ctx->renderer = NULL;
    return ctx;
}

ctx_t * renderer_init (ctx_t * ctx) {
    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
    if (ctx->renderer == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error initializing renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    return ctx;
}
