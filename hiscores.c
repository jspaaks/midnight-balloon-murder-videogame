#include "hiscores.h"
#include "shared.h"
#include <SDL_surface.h>
#include <SDL_video.h>


void hiscores_draw (SDL_Window ** window, SDL_Surface ** screen) {
    shared_draw_background(screen);
    shared_draw_ground(screen);
    SDL_UpdateWindowSurface(*window);
}


void hiscores_update (void) {
}
