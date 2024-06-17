#include "spritesheet.h"
#include "SDL_error.h"
#include "SDL_render.h"
#include "types.h"
#include <stdlib.h>

void spritesheet_deinit (SDL_Texture ** spritesheet) {
    SDL_DestroyTexture(*spritesheet);
    *spritesheet = NULL;
}

SDL_Texture * spritesheet_init (SDL_Renderer * renderer) {
    SDL_Surface * image = SDL_LoadBMP("images/sprites.bmp");
    if (image == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong creating spritesheet surface: %s\n",
                     SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Texture * spritesheet = SDL_CreateTextureFromSurface(renderer, image);
    if (spritesheet == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong creating spritesheet texture: %s\n",
                     SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return spritesheet;
}
