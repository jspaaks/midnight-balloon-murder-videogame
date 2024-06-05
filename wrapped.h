#ifndef WRAPPED_H
#define WRAPPED_H
#include <stdbool.h>
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "SDL_pixels.h"

typedef struct {
    bool invalid;
    SDL_Surface * payload;
} SDLW_Surface;

typedef struct {
    bool invalid;
    SDL_Texture * payload;
} SDLW_Texture;

SDLW_Surface TTFW_RenderText_Shaded(TTF_Font *font, const char *text, SDL_Color fg, SDL_Color bg);
SDLW_Texture SDLW_CreateTextureFromSurface(SDL_Renderer *renderer, SDLW_Surface surface);

#endif
