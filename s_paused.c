#include "s_paused.h"
#include "o_background.h"
#include "context.h"
#include "fsm.h"
#include <SDL_events.h>
#include <SDL_keycode.h>

void paused_draw (ctx_t * ctx) {
    background_draw(ctx);
}

void paused_update (ctx_t * ctx, struct state ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                fprintf(stdout, "playing\n");
                *state = fsm_set_state(PLAYING);
            }
            if (event.key.keysym.sym == SDLK_q) {
                fprintf(stdout, "quitting\n");
                exit(EXIT_SUCCESS);
            }
        }
    }
}
