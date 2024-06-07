#include <stdlib.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "constants.h"
#include "fsm.h"
#include "s_start.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_ground.h"
#include "o_moon.h"

static void s_start_draw_keymap (ctx_t *);
static void s_start_draw_title (ctx_t *);

void s_start_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_moon_draw(ctx);
    o_ground_draw(ctx);
    s_start_draw_title(ctx);
    s_start_draw_keymap(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_start_draw_keymap (ctx_t * ctx) {
    char keymap[20] = "PRESS ENTER TO PLAY";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.lightgray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf.payload->w) / 2,
        .y = SCREEN_HEIGHT - 2 * GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_start_draw_title (ctx_t * ctx) {
    static const struct {
        char left[2];
        char middle[22];
        char right[2];
    } titleparts = {
        .left = "M",
        .middle = "IDNIGHT BALLOON MURDE",
        .right = "R",
    };

    static struct {
        SDLW_Surface left;
        SDLW_Surface middle;
        SDLW_Surface right;
    } surfs;

    static struct {
        SDLW_Texture left;
        SDLW_Texture middle;
        SDLW_Texture right;
    } txres;

    static struct {
        SDL_Rect left;
        SDL_Rect middle;
        SDL_Rect right;
        SDL_Rect underline;
    } tgts;

    surfs.left = TTFW_RenderText_Shaded(ctx->fonts.xxxlarge, titleparts.left, ctx->colors.lightgray, ctx->colors.bg);
    surfs.middle = TTFW_RenderText_Shaded(ctx->fonts.xxlarge, titleparts.middle, ctx->colors.lightgray, ctx->colors.bg);
    surfs.right = TTFW_RenderText_Shaded(ctx->fonts.xxxlarge, titleparts.right, ctx->colors.lightgray, ctx->colors.bg);

    txres.left = SDLW_CreateTextureFromSurface(ctx->renderer, surfs.left);
    txres.middle = SDLW_CreateTextureFromSurface(ctx->renderer, surfs.middle);
    txres.right  = SDLW_CreateTextureFromSurface(ctx->renderer, surfs.right);

    if (txres.left.invalid || txres.middle.invalid || txres.right.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title text.\n");
        exit(EXIT_FAILURE);
    }

    tgts.left = (SDL_Rect){
        .x = (SCREEN_WIDTH - surfs.middle.payload->w) / 2 - surfs.left.payload->w,
        .y = SCREEN_HEIGHT * 0.31 - 7,
        .w = surfs.left.payload->w,
        .h = surfs.left.payload->h,
    };
    tgts.middle = (SDL_Rect){
        .x = (SCREEN_WIDTH - surfs.middle.payload->w) / 2,
        .y = SCREEN_HEIGHT * 0.31,
        .w = surfs.middle.payload->w,
        .h = surfs.middle.payload->h,
    };
    tgts.right = (SDL_Rect){
        .x = (SCREEN_WIDTH - surfs.middle.payload->w) / 2 + surfs.middle.payload->w,
        .y = SCREEN_HEIGHT * 0.31 - 7,
        .w = surfs.right.payload->w,
        .h = surfs.right.payload->h,
    };
    tgts.underline = (SDL_Rect){
        .x = (SCREEN_WIDTH - surfs.middle.payload->w) / 2,
        .y = SCREEN_HEIGHT * 0.31 + surfs.middle.payload->h - 51,
        .w = surfs.middle.payload->w,
        .h = 3,
    };

    SDL_RenderCopy(ctx->renderer, txres.left.payload, NULL, &tgts.left);
    SDL_RenderCopy(ctx->renderer, txres.middle.payload, NULL, &tgts.middle);
    SDL_RenderCopy(ctx->renderer, txres.right.payload, NULL, &tgts.right);
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.lightgray.r,
                                          ctx->colors.lightgray.g,
                                          ctx->colors.lightgray.b,
                                          ctx->colors.lightgray.a);
    SDL_RenderFillRect(ctx->renderer, &tgts.underline);

    SDL_DestroyTexture(txres.left.payload);
    SDL_DestroyTexture(txres.middle.payload);
    SDL_DestroyTexture(txres.right.payload);

    SDL_FreeSurface(surfs.left.payload);
    SDL_FreeSurface(surfs.middle.payload);
    SDL_FreeSurface(surfs.right.payload);

}

ctx_t * s_start_update (ctx_t * ctx, state_t ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                SDL_Log("playing\n");
                *state = fsm_set_state(PLAYING);
            }
        }
    }
    return ctx;
}
