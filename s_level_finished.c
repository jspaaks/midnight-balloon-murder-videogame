#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "fsm.h"
#include "s_playing.h"
#include "s_level_finished.h"
#include "levels.h"
#include "types.h"

#include "o_background.h"
#include "o_barrel.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"

void s_level_finished_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_barrel_draw(ctx);
    o_legend_draw(ctx);
    o_ground_draw(ctx);
    SDL_RenderPresent(ctx->renderer);
}

ctx_t * s_level_finished_update (ctx_t * ctx, state_t ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                ctx->ilevel += ctx->ilevel + 1 < ctx->nlevels ? 1 : 0;
                levels_set(ctx, ctx->ilevel);
                SDL_Log("playing\n");
                *state = fsm_set_state(PLAYING);
            }
        }
    }
    return ctx;
}
