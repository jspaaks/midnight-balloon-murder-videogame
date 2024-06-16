#include "SDL_pixels.h"
#include "colors.h"
#include "types.h"

colors_t colors_init (void) {
    return (colors_t) {
        .bg         = (SDL_Color) { .r =   0, .g =  22, .b =  43, .a =   0 },
        .green      = (SDL_Color) { .r =   0, .g = 161, .b =   0, .a =   0 },
        .ground     = (SDL_Color) { .r =  11, .g =   1, .b =  26, .a =   0 },
        .hit        = (SDL_Color) { .r =   0, .g = 161, .b =   0, .a =   0 },
        .lightgray  = (SDL_Color) { .r = 200, .g = 200, .b = 200, .a =   0 },
        .magenta    = (SDL_Color) { .r = 200, .g =   0, .b = 255, .a =   0 },
        .middlegray = (SDL_Color) { .r = 100, .g = 100, .b = 100, .a =   0 },
        .miss       = (SDL_Color) { .r = 200, .g =   0, .b =   0, .a =   0 },
        .orange     = (SDL_Color) { .r = 200, .g = 161, .b =   0, .a =   0 },
        .red        = (SDL_Color) { .r = 200, .g =   0, .b =   0, .a =   0 },
        .white      = (SDL_Color) { .r = 255, .g = 255, .b = 255, .a =   0 },
    };
}
