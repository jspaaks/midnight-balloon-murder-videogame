#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_render.h"
#include "spritesheet.h"
#include "types.h"

ctx_t * spritesheet_deinit (ctx_t * ctx) {
    SDL_DestroyTexture(ctx->spritesheet);
    ctx->spritesheet = NULL;
    return ctx;
}

ctx_t * spritesheet_init (ctx_t * ctx) {
    SDL_Surface * image = SDL_LoadBMP("img/sprites.bmp");
    if (image == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong creating spritesheet surface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ctx->spritesheet = SDL_CreateTextureFromSurface(ctx->renderer, image);
    if (ctx->spritesheet == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong creating spritesheet texture: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ctx;
}
