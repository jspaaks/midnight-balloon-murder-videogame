#include "constants.h"
#include "shared.h"
#include <SDL_surface.h>

void shared_draw_background (SDL_Surface ** screen) {
    SDL_PixelFormat * fmt = (*screen)->format;
    Uint32 color = SDL_MapRGBA(fmt, 0, 22, 43, 0);
    SDL_FillRect(*screen, NULL, color);
}

void shared_draw_ground (SDL_Surface ** screen) {
    static const int ground_height = 100;
    static const SDL_Rect rect = {
        .x = 0,
        .y = SCREEN_HEIGHT - ground_height,
        .w = SCREEN_WIDTH,
        .h = ground_height,
    };
    SDL_PixelFormat * fmt = (*screen)->format;
    Uint32 color = SDL_MapRGBA(fmt, 11, 1, 26, 0);
    SDL_FillRect(*screen, &rect, color);
}

void shared_draw_turret_base (SDL_Surface ** screen) {
    static const int ground_height = 100;
    static const int turret_base_height = 25;
    static const SDL_Rect rect = {
        .x = 180,
        .y = SCREEN_HEIGHT - ground_height - turret_base_height,
        .w = 70,
        .h = 25,
    };
    SDL_PixelFormat * fmt = (*screen)->format;
    Uint32 color = SDL_MapRGBA(fmt, 50, 64, 46, 0);
    SDL_FillRect(*screen, &rect, color);
}
