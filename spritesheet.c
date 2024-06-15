#include <stdlib.h>
#include "SDL_error.h"
#include "SDL_render.h"
#include "spritesheet.h"
#include "types.h"

void spritesheet_deinit (SDL_Texture ** spritesheet) {
    SDL_DestroyTexture(*spritesheet);
    *spritesheet = NULL;
}

void spritesheet_init (SDL_Renderer * renderer, SDL_Texture ** spritesheet) {
    SDL_Surface * image = SDL_LoadBMP("img/sprites.bmp");
    if (image == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong creating spritesheet surface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    *spritesheet = SDL_CreateTextureFromSurface(renderer, image);
    if (*spritesheet == NULL) {
        SDL_LogError(SDL_ENOMEM, "Something went wrong creating spritesheet texture: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}
