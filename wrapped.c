#include "wrapped.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <stdbool.h>

SDLW_Surface TTFW_RenderText_Shaded (TTF_Font * font, const char * text, SDL_Color fg,
                                     SDL_Color bg) {
    SDL_Surface * surf = TTF_RenderText_Shaded(font, text, fg, bg);
    return (SDLW_Surface){
        .payload = surf,
        .invalid = surf == NULL,
    };
}

SDLW_Texture SDLW_CreateTextureFromSurface (SDL_Renderer * renderer, SDLW_Surface surface) {
    if (surface.invalid) {
        return (SDLW_Texture){
            .invalid = false,
            .payload = NULL,
        };
    }
    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surface.payload);
    return (SDLW_Texture){
        .payload = txre,
        .invalid = txre == NULL,
    };
}
