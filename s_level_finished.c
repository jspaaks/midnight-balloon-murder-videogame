#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "constants.h"
#include "fsm.h"
#include "s_playing.h"
#include "s_level_finished.h"
#include "levels.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_barrel.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"

static void s_paused_draw_title (ctx_t *);

void s_level_finished_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_barrel_draw(ctx);
    o_legend_draw(ctx);
    o_ground_draw(ctx);
    s_paused_draw_title(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_paused_draw_title (ctx_t * ctx) {
    char title[15];
    if (ctx->nmiss == 0) {
        strncpy(title, "PERFECT SCORE!", 15);
    } else {
        strncpy(title, "LEVEL FINISHED", 15);
    }
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.large, title, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf.payload->w) / 2,
        .y = SCREEN_HEIGHT * 0.31,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
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
