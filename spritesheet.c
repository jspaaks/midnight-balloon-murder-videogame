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
        SDL_Log("Something went wrong loading spritesheet.\n");
        exit(EXIT_FAILURE);
    }
    ctx->spritesheet = SDL_CreateTextureFromSurface(ctx->renderer, image);
    return ctx;
}
