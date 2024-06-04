#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include "constants.h"
#include "types.h"
#include "window.h"

ctx_t * window_deinit(ctx_t * ctx) {
    SDL_DestroyWindow(ctx->window);
    ctx->window = NULL;
    return ctx;
}

ctx_t * window_init(ctx_t * ctx) {
    ctx->window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_BORDERLESS);
    if (ctx->window == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ctx;
}
