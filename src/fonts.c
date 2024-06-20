#include "deinit.h"
#include "fonts.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "types.h"
#include <stdlib.h>

void fonts_deinit (fonts_t * fonts) {
    TTF_CloseFont(fonts->regular);
    TTF_CloseFont(fonts->large);
    TTF_CloseFont(fonts->xlarge);
    TTF_CloseFont(fonts->xxlarge);
    TTF_CloseFont(fonts->xxxlarge);
    fonts->regular = NULL;
    fonts->large = NULL;
    fonts->xlarge = NULL;
    fonts->xxlarge = NULL;
    fonts->xxxlarge = NULL;
    TTF_Quit();
}

fonts_t fonts_init (void) {
    if (TTF_Init() != 0) {
        SDL_LogError(SDL_ENOMEM, "Couldn't initialize SDL_ttf: %s", TTF_GetError());
        deinit();
    }
    const char fontfile[] = "fonts/Bayon-Regular.ttf";
    int ptsize;

    fonts_t fonts;

    ptsize = 20;
    fonts.regular = TTF_OpenFont(fontfile, ptsize);
    if (fonts.regular == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile,
                     TTF_GetError());
        deinit();
    }

    ptsize = 32;
    fonts.large = TTF_OpenFont(fontfile, ptsize);
    if (fonts.large == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile,
                     TTF_GetError());
        deinit();
    }

    ptsize = 70;
    fonts.xlarge = TTF_OpenFont(fontfile, ptsize);
    if (fonts.large == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile,
                     TTF_GetError());
        deinit();
    }

    ptsize = 100;
    fonts.xxlarge = TTF_OpenFont(fontfile, ptsize);
    if (fonts.xlarge == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile,
                     TTF_GetError());
        deinit();
    }

    ptsize = 114;
    fonts.xxxlarge = TTF_OpenFont(fontfile, ptsize);
    if (fonts.xxlarge == NULL) {
        SDL_LogError(SDL_ENOMEM, "Couldn't load %d pt font from %s: %s\n", ptsize, fontfile,
                     TTF_GetError());
        deinit();
    }

    return fonts;
}
