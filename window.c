#include <assert.h>
#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include "types.h"
#include "window.h"

ctx_t * window_deinit(ctx_t * ctx) {
    SDL_DestroyWindow(ctx->window);
    ctx->window = NULL;
    return ctx;
}

ctx_t * window_init(ctx_t * ctx) {
    assert(ctx->scene.tgt.w != 0 && "scene needs to be initialized before window");
    int flags = SDL_WINDOW_RESIZABLE;
    ctx->window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, ctx->scene.tgt.w, ctx->scene.tgt.h, flags);
    if (ctx->window == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_ShowCursor(SDL_DISABLE);
    ctx->isfullscreen = false;
    return ctx;
}
