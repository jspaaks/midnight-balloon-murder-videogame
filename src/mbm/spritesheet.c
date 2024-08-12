#include "mbm/spritesheet.h"
#include "mbm/deinit.h"
#include "SDL_error.h"
#include "SDL_render.h"
#include "mbm/types.h"
#include <stdlib.h>

void spritesheet_deinit (SDL_Texture ** spritesheet) {
    if (spritesheet == NULL) return;
    SDL_DestroyTexture(*spritesheet);
    *spritesheet = NULL;
}

SDL_Texture * spritesheet_init (SDL_Renderer * renderer, char * basepath) {
    char filename[1024];
    sprintf(filename, "%s../assets/images/sprites.bmp", basepath);
    SDL_Surface * image = SDL_LoadBMP(filename);
    if (image == NULL) {
        SDL_Log("Something went wrong creating spritesheet surface: %s\n", SDL_GetError());
        deinit();
    }
    SDL_Texture * spritesheet = SDL_CreateTextureFromSurface(renderer, image);
    if (spritesheet == NULL) {
        SDL_Log("Something went wrong creating spritesheet texture: %s\n", SDL_GetError());
        deinit();
    }
    return spritesheet;
}
