#include "SDL_pixels.h"
#include "colors.h"
#include "types.h"

ctx_t * colors_init (ctx_t * ctx) {
    ctx->colors = (colors_t) {
        .bg      = (SDL_Color) { .r =   0, .g =  22, .b =  43, .a = 0 },
        .green   = (SDL_Color) { .r =   0, .g = 161, .b =   0, .a = 0 },
        .hit     = (SDL_Color) { .r =   0, .g = 161, .b =   0, .a = 0 },
        .magenta = (SDL_Color) { .r = 200, .g =   0, .b = 255, .a = 0 },
        .middle  = (SDL_Color) { .r = 128, .g = 128, .b = 128, .a = 0 },
        .miss    = (SDL_Color) { .r = 200, .g =   0, .b =   0, .a = 0 },
        .orange  = (SDL_Color) { .r = 200, .g = 161, .b =   0, .a = 0 },
        .red     = (SDL_Color) { .r = 200, .g =   0, .b =   0, .a = 0 },
        .white   = (SDL_Color) { .r = 255, .g = 255, .b = 255, .a = 0 },
    };
    return ctx;
}