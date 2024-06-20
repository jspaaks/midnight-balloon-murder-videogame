#include "deinit.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include "types.h"
#include "window.h"
#include <assert.h>
#include <stdlib.h>

void window_deinit (SDL_Window ** window) {
    SDL_DestroyWindow(*window);
    *window = NULL;
}

SDL_Window * window_init (scene_t scene) {
    assert(scene.tgt.w != 0 && "scene needs to be initialized before window");
    int flags = SDL_WINDOW_RESIZABLE;
    SDL_Window * window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, scene.tgt.w, scene.tgt.h, flags);
    if (window == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating window: %s\n", SDL_GetError());
        deinit();
    }
    return window;
}
