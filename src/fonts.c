#include "fonts.h"
#include "deinit.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "types.h"
#include <stdlib.h>

void fonts_deinit (fonts_t * fonts) {
    if (fonts == NULL) return;
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

fonts_t fonts_init (char * basepath) {
    if (TTF_Init() != 0) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", TTF_GetError());
        deinit();
    }
    char filename[1024];
    int ptsize;
    fonts_t fonts;

    sprintf(filename, "%s../fonts/Bayon-Regular.ttf", basepath);

    ptsize = 20;
    fonts.regular = TTF_OpenFont(filename, ptsize);
    if (fonts.regular == NULL) {
        SDL_Log(filename,
                     TTF_GetError());
        deinit();
    }

    ptsize = 32;
    fonts.large = TTF_OpenFont(filename, ptsize);
    if (fonts.large == NULL) {
        SDL_Log(filename,
                     TTF_GetError());
        deinit();
    }

    ptsize = 70;
    fonts.xlarge = TTF_OpenFont(filename, ptsize);
    if (fonts.large == NULL) {
        SDL_Log(filename,
                     TTF_GetError());
        deinit();
    }

    ptsize = 100;
    fonts.xxlarge = TTF_OpenFont(filename, ptsize);
    if (fonts.xlarge == NULL) {
        SDL_Log(filename,
                     TTF_GetError());
        deinit();
    }

    ptsize = 114;
    fonts.xxxlarge = TTF_OpenFont(filename, ptsize);
    if (fonts.xxlarge == NULL) {
        SDL_Log(filename,
                     TTF_GetError());
        deinit();
    }

    return fonts;
}
