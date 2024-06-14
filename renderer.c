#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_hints.h"
#include "renderer.h"
#include "types.h"

void renderer_deinit (SDL_Renderer ** renderer) {
    SDL_DestroyRenderer(*renderer);
    *renderer = NULL;
}

void renderer_init (ctx_t * ctx, SDL_Renderer ** renderer) {
    *renderer = SDL_CreateRenderer(ctx->window, -1, 0);
    if (*renderer == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error initializing renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}
