#include <stdlib.h>
#include "SDL_ttf.h"
#include "SDL_log.h"
#include "types.h"
#include "fonts.h"

void fonts_deinit(ctx_t * ctx) {
    TTF_CloseFont(ctx->fonts.regular);
    TTF_CloseFont(ctx->fonts.large);
    TTF_CloseFont(ctx->fonts.xlarge);
    TTF_CloseFont(ctx->fonts.xxlarge);
    TTF_CloseFont(ctx->fonts.xxxlarge);
    ctx->fonts.regular = NULL;
    ctx->fonts.large = NULL;
    ctx->fonts.xlarge = NULL;
    ctx->fonts.xxlarge = NULL;
    ctx->fonts.xxxlarge = NULL;
    TTF_Quit();
}

void fonts_init(ctx_t * ctx) {
    if (TTF_Init() != 0) {
        SDL_LogError(SDL_ENOMEM, "Couldn't initialize SDL_ttf: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    const char fontfile[] = "fonts/Bayon-Regular.ttf";
    int ptsize;

    ptsize = 20;
    ctx->fonts.regular = TTF_OpenFont(fontfile, ptsize);
    if (ctx->fonts.regular == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, TTF_GetError());
    }

    ptsize = 32;
    ctx->fonts.large = TTF_OpenFont(fontfile, ptsize);
    if (ctx->fonts.large == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, TTF_GetError());
    }

    ptsize = 70;
    ctx->fonts.xlarge = TTF_OpenFont(fontfile, ptsize);
    if (ctx->fonts.large == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, TTF_GetError());
    }

    ptsize = 100;
    ctx->fonts.xxlarge = TTF_OpenFont(fontfile, ptsize);
    if (ctx->fonts.xlarge == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, TTF_GetError());
    }

    ptsize = 114;
    ctx->fonts.xxxlarge = TTF_OpenFont(fontfile, ptsize);
    if (ctx->fonts.xxlarge == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, TTF_GetError());
    }
}
