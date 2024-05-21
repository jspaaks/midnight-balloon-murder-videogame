#include "constants.h"
#include "fsm.h"
#include "SDL.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <stdio.h>
#include <stdlib.h>

void deinit (SDL_Window **);
void init (SDL_Window **, SDL_Surface **);

void deinit (SDL_Window ** window) {
    SDL_DestroyWindowSurface(*window);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

void init (SDL_Window ** window, SDL_Surface ** screen) {
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    }

    *window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_RESIZABLE);
    if (*window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    }

    *screen = SDL_GetWindowSurface(*window);
    if (*screen == NULL) {
        fprintf(stderr, "Error getting window surface: %s\n", SDL_GetError());
    }
}

int main (void) {

    SDL_Window * window = NULL;
    SDL_Surface * screen = NULL;
    state_t * game = NULL;

    init(&window, &screen);

    game = fsm_set_state(PLAYING);
    game->draw(&window, &screen);
    SDL_Delay(3000);

    game = fsm_set_state(HISCORES);
    game->draw(&window, &screen);
    SDL_Delay(3000);

    deinit(&window);
    return EXIT_SUCCESS;
}
