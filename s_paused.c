#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "types.h"
#include "fsm.h"
#include "s_paused.h"
#include "o_background.h"

void s_paused_draw (ctx_t * ctx) {
    o_background_draw(ctx);
}

ctx_t * s_paused_update (ctx_t * ctx, state_t ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_Log("playing\n");
                *state = fsm_set_state(PLAYING);
            }
            if (event.key.keysym.sym == SDLK_q) {
                SDL_Log("quitting\n");
                exit(EXIT_SUCCESS);
            }
        }
    }
    return ctx;
}
