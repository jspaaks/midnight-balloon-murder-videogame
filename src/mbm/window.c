#include "mbm/window.h"
#include "mbm/deinit.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include "mbm/types.h"
#include <assert.h>
#include <stdlib.h>

void window_deinit (SDL_Window ** window) {
    if (window == NULL) return;
    SDL_DestroyWindow(*window);
    *window = NULL;
}

SDL_Window * window_init (const scene_t scene) {
    assert(scene.tgt.w != 0 && "scene needs to be initialized before window");
    int flags = SDL_WINDOW_RESIZABLE;
    SDL_Window * window = SDL_CreateWindow("Midnight Balloon Murder", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, scene.tgt.w, scene.tgt.h, flags);
    if (window == NULL) {
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        deinit();
    }
    return window;
}
