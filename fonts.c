#include "SDL_ttf.h"
#include "types.h"
#include "fonts.h"

ctx_t * fonts_init(ctx_t * ctx) {
    if (TTF_Init() != 0) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    int ptsize = 20;
    char fontfile[] = "fonts/Bayon-Regular.ttf";
    TTF_Font * font = TTF_OpenFont(fontfile, ptsize);
    if (font == NULL) {
        SDL_LogError(0, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile, SDL_GetError());
    }
    ctx->font = font;
    return ctx;
}

ctx_t * fonts_deinit(ctx_t * ctx) {
    TTF_CloseFont(ctx->font);
    ctx->font = NULL;

    TTF_Quit();
    return ctx;
}
