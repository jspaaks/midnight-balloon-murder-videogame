#ifndef WRAPPED_H
#define WRAPPED_H
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <stdbool.h>

typedef struct {
    bool invalid;
    SDL_Surface * payload;
} SDLW_Surface;

typedef struct {
    bool invalid;
    SDL_Texture * payload;
} SDLW_Texture;

SDLW_Surface TTFW_RenderText_Shaded (TTF_Font *, const char *, SDL_Color, SDL_Color);
SDLW_Texture SDLW_CreateTextureFromSurface (SDL_Renderer *, SDLW_Surface);

#endif
