#include "playing.h"
#include "shared.h"
#include <SDL_surface.h>
#include <SDL_video.h>

void playing_draw (SDL_Window ** window, SDL_Surface ** screen) {
    shared_draw_background(screen);
    shared_draw_ground(screen);
    shared_draw_turret_base(screen);
    SDL_UpdateWindowSurface(*window);
}

void playing_update (void) {
}
